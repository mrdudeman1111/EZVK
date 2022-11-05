// #ifdef GLFWAPP

#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <EkImages.hpp>
#include <EkTypes.hpp>
#include <EkPipeline.hpp>

struct EkWindow
{
public:
    VkSwapchainKHR Swapchain;
    GLFWwindow *Window = NULL;
    VkPhysicalDevice *PhysDevPtr;
    VkSurfaceKHR Surface;
    VkFormat ImageFormat;
    
    const char **GlfwExts;
    uint32_t glfwExtCount = 0;
    VkExtent3D ImageExtents;
    DeleteQueue CleanupQueue;
    uint32_t BufferCount = 2;  // This is filled with user given data at swapchain creation
    std::vector<FrameBuffer> FrameBuffers;

    ~EkWindow()
    {
        CleanupQueue.Run();
    }

    VkSurfaceFormatKHR QueryFormats(VkFormat FormatTarget)
    {
        uint32_t FormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(*PhysDevPtr, Surface, &FormatCount, NULL);

        std::vector<VkSurfaceFormatKHR> Formats(FormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(*PhysDevPtr, Surface, &FormatCount, Formats.data());

        for(const VkSurfaceFormatKHR &Format : Formats)
        {
            if (Format.format == FormatTarget)
            {
                return Format;
            }
        }
        return Formats[0];
    }

    VkPresentModeKHR QueryPresentModes(VkPresentModeKHR ModeTarget)
    {
        uint32_t SurfaceModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(*PhysDevPtr, Surface, &SurfaceModeCount, nullptr);

        std::vector<VkPresentModeKHR> PresentModes(SurfaceModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(*PhysDevPtr, Surface, &SurfaceModeCount, PresentModes.data());

        for (const VkPresentModeKHR &Mode : PresentModes)
        {
            if (Mode == ModeTarget)
            {
                return Mode;
            }
        }
        return PresentModes[0];
    }

    EkWindow *CreateWindow(int Width, int Height, std::string AppName)
    {
        ImageExtents = VkExtent3D{static_cast<uint32_t>(Width), static_cast<uint32_t>(Height), 1};
        glfwInit();

        if (glfwVulkanSupported() != GLFW_TRUE)
        {
            ThrowError("GLFW: Vulkan Not Supported");
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        Window = glfwCreateWindow(Width, Height, AppName.c_str(), nullptr, nullptr);

        GlfwExts = glfwGetRequiredInstanceExtensions(&glfwExtCount);

        CleanupQueue([this]()
                     { glfwDestroyWindow(Window); glfwTerminate(); std::cout << "Deleted and terminated glfwWindow\n"; });
        return this;
    }

    void CreateSurface(VkInstance *Instance)
    {
        VkResult Result = glfwCreateWindowSurface(*Instance, Window, nullptr, &Surface);
        if (Result != VK_SUCCESS)
        {
            std::cout << "Error: " << Result << std::endl;
            ThrowError("GLFW: Can't create window surface");
        }

        CleanupQueue([this, Instance]()
                     { vkDestroySurfaceKHR(*Instance, Surface, nullptr); std::cout << "Deleted surface"; });
    }

    void CreateSwapchain(uint32_t GraphicsFamilyIndex, VkPresentModeKHR PresentationMode)
    {
        VkSurfaceFormatKHR SurfaceFormat = QueryFormats(VK_FORMAT_R32G32B32_SFLOAT);
        ImageFormat = SurfaceFormat.format;

        VkSurfaceCapabilitiesKHR SurfaceCapabilites;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*PhysDevPtr, Surface, &SurfaceCapabilites);

        VkSwapchainCreateInfoKHR SwapchainInfo{};
        SwapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        SwapchainInfo.surface = Surface;
        SwapchainInfo.clipped = VK_TRUE;
        SwapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        SwapchainInfo.preTransform = SurfaceCapabilites.currentTransform;
        SwapchainInfo.presentMode = PresentationMode;

        SwapchainInfo.minImageCount = SurfaceCapabilites.minImageCount;
        SwapchainInfo.imageFormat = SurfaceFormat.format;
        SwapchainInfo.imageColorSpace = SurfaceFormat.colorSpace;
        SwapchainInfo.imageExtent = VkExtent2D{ ImageExtents.width, ImageExtents.height };
        SwapchainInfo.imageArrayLayers = 1;
        SwapchainInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        SwapchainInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if(vkCreateSwapchainKHR(GlobDevice, &SwapchainInfo, nullptr, &Swapchain) != VK_SUCCESS)
        {
            ThrowError("failed to create a swapchain.");
        }

        std::vector<VkImage> SwapImagesRaw(BufferCount);
        vkGetSwapchainImagesKHR(GlobDevice, Swapchain, &BufferCount, SwapImagesRaw.data());
        FrameBuffers.resize(SwapImagesRaw.size());
        
        std::cout << "Successfully made " << SwapImagesRaw.size() << " Framebuffers\n";

        for(uint32_t i = 0; i < SwapImagesRaw.size(); i++)
        {
            // Create ImageBuffer
                AllocatedImage ImageBuffer{};
                ImageBuffer.Image = SwapImagesRaw[i];
                ImageBuffer.Format = SurfaceFormat.format;

            // Create DepthBuffer
                AllocatedImage DepthBuffer{};
                if(Image::AllocateImage(VK_IMAGE_TYPE_2D, ImageExtents, VK_FORMAT_D32_SFLOAT, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VMA_MEMORY_USAGE_GPU_ONLY, 1, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, &DepthBuffer) == false)
                {
                    ThrowError("Failed to create depth buffer for swapchain");
                }

            // Create FrameBuffer
                FrameBuffer FB(ImageBuffer, DepthBuffer);
                Image::BuildFrameBufferImages(ImageExtents, ImageFormat, &FB, VK_IMAGE_VIEW_TYPE_2D);
                FrameBuffers.push_back(FB);
                // Working, Imageview and type still full
        }

        FrameBuffers.shrink_to_fit();

        CleanupQueue([this]()
                     { vkDeviceWaitIdle(GlobDevice); vkDestroySwapchainKHR(GlobDevice, Swapchain, nullptr); std::cout << "Deleted Swapchain\n"; });
    }

    VkExtent2D GetWindowExtent()
    {
        int Height, Width;
        glfwGetFramebufferSize(Window, &Width, &Height);
        VkExtent2D ReturnExtent = { static_cast<uint32_t>(Height), static_cast<uint32_t>(Width) };
        return ReturnExtent;
    }

    Ek::Subpass GetFrameBufferPass(uint32_t IndexOffset)
    {
        Ek::Subpass WindowPass{};
        WindowPass.Build(&FrameBuffers[0].ImageBuffer, &FrameBuffers[0].DepthBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, IndexOffset);
        // ImageView and type still valid
        return WindowPass;
    }

};

// #endif
