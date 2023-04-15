#ifdef GLFWAPP

#include <Base/EkWindow.hpp>
#include <Base/Device.h>

namespace Ek
{
    void Window::QueryFormats()
    {
        uint32_t FormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(*pPhysicalDevice, Surface, &FormatCount, nullptr);

        std::vector<VkSurfaceFormatKHR> AvFormats(FormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(*pPhysicalDevice, Surface, &FormatCount, AvFormats.data());

        SurfaceFormat = AvFormats[0];
    }

    void Window::CreateSurface()
    {
        VkResult Res = glfwCreateWindowSurface(*pInst, glfwWindow, nullptr, &Surface);

        if (Res != VK_SUCCESS)
        {
            std::cout << "Failed to create Window Surface: " << Res << std::endl;
            throw std::runtime_error("Failed to Create surface");
        }

        VkInstance *InstanceHandle = pInst;
        VkSurfaceKHR *SurfaceHandle = &Surface;
        DelQueue([InstanceHandle, SurfaceHandle]
                      { vkDestroySurfaceKHR(*InstanceHandle, *SurfaceHandle, nullptr); });
    }

    void Window::CreateWindow(int Width, int Height, const char *WindowName)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        glfwWindow = glfwCreateWindow(Width, Height, WindowName, nullptr, nullptr);

        WindowExtent.depth = 1.f;
        WindowExtent.height = Height;
        WindowExtent.width = Width;

        GLFWwindow *WindowHandle = glfwWindow;
        DelQueue([WindowHandle]{ glfwDestroyWindow(WindowHandle); });
    }

    void Window::CreateSwapchain(uint32_t DesiredFBCount)
    {
        VkSurfaceCapabilitiesKHR SurfaceCap;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*pPhysicalDevice, Surface, &SurfaceCap);

        QueryFormats();

        VkSwapchainCreateInfoKHR SwapCI{};
        SwapCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;

        SwapCI.imageFormat = SurfaceFormat.format;
        SwapCI.imageColorSpace = SurfaceFormat.colorSpace;
        SwapCI.imageExtent.height = WindowExtent.height;
        SwapCI.imageExtent.width = WindowExtent.width;
        SwapCI.imageArrayLayers = 1;
        SwapCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        SwapCI.surface = Surface;

        SwapCI.preTransform = SurfaceCap.currentTransform;
        SwapCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        SwapCI.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;
        SwapCI.clipped = VK_TRUE;

        SwapCI.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        SwapCI.oldSwapchain = VK_NULL_HANDLE;

        if (DesiredFBCount >= SurfaceCap.minImageCount)
        {
            SwapCI.minImageCount = DesiredFBCount;
        }
        else
        {
            SwapCI.minImageCount = SurfaceCap.minImageCount;
            std::cout << "Desired framebuffer count is not possible. Creating " << SwapCI.minImageCount << " Framebuffers instead.\n";
        }

        SwapCI.imageArrayLayers = 1;

        if(vkCreateSwapchainKHR(pDev->VkDev, &SwapCI, nullptr, &Swapchain) != VK_SUCCESS)
        {
            ThrowError("Failed to create swapchain");
        }

        if(DesiredFBCount >= SurfaceCap.minImageCount)
        {
            FrameBuffers.resize(DesiredFBCount);
            VkImage SwapImages[DesiredFBCount];
            vkGetSwapchainImagesKHR(pDev->VkDev, Swapchain, &DesiredFBCount, SwapImages);

            for(uint32_t i = 0; i < DesiredFBCount; i++)
            {
                AllocatedImage Depth = pDev->CreateTexture(VK_IMAGE_TYPE_3D, WindowExtent, VK_FORMAT_D16_UNORM, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VMA_MEMORY_USAGE_GPU_ONLY, 1, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);

                AllocatedImage Color(&pDev->VkDev);
                Color.Image = SwapImages[i];
                Color.Type = RtType::RtColor;
                Color.Layout = VK_IMAGE_LAYOUT_UNDEFINED;

                FrameBuffers[i] = new FrameBuffer(&pDev->VkDev);
                FrameBuffers[i]->InitImages(&Color, &Depth, VK_IMAGE_VIEW_TYPE_3D);
            }
        }
        else
        {
            FrameBuffers.resize(SurfaceCap.minImageCount);
            VkImage SwapImages[SurfaceCap.minImageCount];
            vkGetSwapchainImagesKHR(pDev->VkDev, Swapchain, &SurfaceCap.minImageCount, SwapImages);

            for(uint32_t i = 0; i < SurfaceCap.minImageCount; i++)
            {
                AllocatedImage Depth = pDev->CreateTexture(VK_IMAGE_TYPE_3D, WindowExtent, VK_FORMAT_D16_UNORM, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL, VMA_MEMORY_USAGE_GPU_ONLY, 1, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);

                AllocatedImage Color(&pDev->VkDev);
                Color.Image = SwapImages[i];
                Color.Type = RtType::RtColor;
                Color.Layout = VK_IMAGE_LAYOUT_UNDEFINED;

                FrameBuffers[i] = new FrameBuffer(&pDev->VkDev);
                FrameBuffers[i]->InitImages(&Color, &Depth, VK_IMAGE_VIEW_TYPE_3D);
            }
        }
    }

    FrameBuffer* Window::GetNextFrame(VkSemaphore* WaitSemaphore, VkFence* Fence)
    {
        if(vkAcquireNextImageKHR(pDev->VkDev, Swapchain, UINT64_MAX, *WaitSemaphore, *Fence, &CurrentFrameIndex) != VK_SUCCESS)
        {
            ThrowError("Failed to acquire next Swapchain image, Returning with Invalid FrameBuffer\n");
        }
        return FrameBuffers[CurrentFrameIndex];
    }

    void Window::cmdPresentFrame(uint32_t WaitSemaphoreCount, VkSemaphore* WaitSemaphores)
    {
        VkPresentInfoKHR PresentInf{};
        PresentInf.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        PresentInf.pImageIndices = &CurrentFrameIndex;

        PresentInf.swapchainCount = 1;
        PresentInf.pSwapchains = &Swapchain;

        PresentInf.waitSemaphoreCount = WaitSemaphoreCount;
        PresentInf.pWaitSemaphores = WaitSemaphores;

        vkQueuePresentKHR(*pPresentQueue, &PresentInf);

        CurrentFrameIndex = (CurrentFrameIndex++) % 3;
    }
}

#endif
