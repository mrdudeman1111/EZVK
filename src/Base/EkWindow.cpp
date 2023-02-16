#ifdef GLFWAPP

#include <Base/EkWindow.hpp>

extern VkInstance Instance;
extern VkDevice Device;
extern VkPhysicalDevice PhysicalDevice;
extern DeleteQueue DeletionQueue;

namespace Ek
{
    Window::Window()
    {
        glfwInit();

        const char **Extensions = glfwGetRequiredInstanceExtensions(&glfwExtCount);

        for (uint32_t i = 0; i < glfwExtCount; i++)
        {
            glfwExts.push_back(Extensions[i]);
        }

        DeletionQueue([]
                      { glfwTerminate(); });
    }

    void Window::QueryFormats()
    {
        uint32_t FormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, nullptr);

        std::vector<VkSurfaceFormatKHR> AvFormats(FormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, AvFormats.data());

        SurfaceFormat = AvFormats[0];
    }

    void Window::CreateSurface()
    {
        VkResult Res = glfwCreateWindowSurface(Instance, glfwWindow, nullptr, &Surface);

        if (Res != VK_SUCCESS)
        {
            std::cout << "Failed to create Window Surface: " << Res << std::endl;
            throw std::runtime_error("Failed to Create surface");
        }

        VkInstance *InstanceHandle = &Instance;
        VkSurfaceKHR *SurfaceHandle = &Surface;
        DeletionQueue([InstanceHandle, SurfaceHandle]
                      { vkDestroySurfaceKHR(*InstanceHandle, *SurfaceHandle, nullptr); });
    }

    void Window::CreateWindow(int Width, int Height, const char *WindowName)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        glfwWindow = glfwCreateWindow(Width, Height, WindowName, nullptr, nullptr);

        WindowWidth = Width;
        WindowHeight = Height;

        GLFWwindow *WindowHandle = glfwWindow;

        DeletionQueue([WindowHandle]
                      { glfwDestroyWindow(WindowHandle); });
    }

    void Window::CreateSwapchain(uint32_t DesiredFBCount)
    {
        VkSurfaceCapabilitiesKHR SurfaceCap;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysicalDevice, Surface, &SurfaceCap);

        VkSwapchainCreateInfoKHR SwapCI{};
        SwapCI.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        SwapCI.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        SwapCI.surface = Surface;
        SwapCI.imageColorSpace = SurfaceFormat.colorSpace;
        SwapCI.imageFormat = SurfaceFormat.format;
        SwapCI.imageExtent.height = WindowHeight;
        SwapCI.imageExtent.width = WindowWidth;
        SwapCI.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        SwapCI.queueFamilyIndexCount = 1;
        SwapCI.pQueueFamilyIndices = &PresentFamily;
        SwapCI.presentMode = VK_PRESENT_MODE_MAILBOX_KHR;

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

        if(vkCreateSwapchainKHR(Device, &SwapCI, nullptr, &Swapchain) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create swapchain.\nAborting...");
        }

        if(DesiredFBCount >= SurfaceCap.minImageCount)
        {
            FrameBuffers.resize(DesiredFBCount);
            VkImage SwapImages[DesiredFBCount];
            vkGetSwapchainImagesKHR(Device, Swapchain, &DesiredFBCount, SwapImages);

            for(uint32_t i = 0; i < DesiredFBCount; i++)
            {
                FrameBuffers[i].ImageBuffer.Image = SwapImages[i];
            }
        }
        else
        {
            FrameBuffers.resize(SurfaceCap.minImageCount);
            VkImage SwapImages[SurfaceCap.minImageCount];
            vkGetSwapchainImagesKHR(Device, Swapchain, &SurfaceCap.minImageCount, SwapImages);

            for(uint32_t i = 0; i < SurfaceCap.minImageCount; i++)
            {
                FrameBuffers[i].ImageBuffer.Image = SwapImages[i];
            }
        }

        for(FrameBuffer& FB : FrameBuffers)
        {
            Image::BuildFrameBuffer;
        }
    }
}

#endif
