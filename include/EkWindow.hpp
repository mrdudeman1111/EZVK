#ifdef GLFWAPP

#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

struct EkWindow
{
    public:
    GLFWwindow* Window = NULL;
    VkPhysicalDevice* PhysDevPtr;
    const char** GlfwExts;
    uint32_t glfwExtCount = 0;
    VkSurfaceKHR Surface;
    VkExtent2D ImageExtents;
    DeleteQueue CleanupQueue;
    uint32_t BufferCount = 2;
    VkSwapchainKHR Swapchain;
    
    std::vector<AllocatedImage> ImageBuffers;
    std::vector<VkFramebuffer> FrameBuffers;

    ~EkWindow()
    {
        CleanupQueue.Run();
    }

    VkSurfaceFormatKHR QueryFormats(VkFormat FormatTarget)
    {
        uint32_t FormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(*PhysDevPtr, Surface, &FormatCount, nullptr);

        std::vector<VkSurfaceFormatKHR> Formats(FormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(*PhysDevPtr, Surface, &FormatCount, Formats.data());


        for(const VkSurfaceFormatKHR& Format : Formats)
        {
            if(Format.format == FormatTarget)
            {
                return Format;
            }
            std::cout << Format.format << std::endl;
        }
        return Formats[0];
    }

    VkPresentModeKHR QueryPresentModes(VkPresentModeKHR ModeTarget)
    {
        uint32_t SurfaceModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(*PhysDevPtr, Surface, &SurfaceModeCount, nullptr);

        std::vector<VkPresentModeKHR> PresentModes(SurfaceModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(*PhysDevPtr, Surface, &SurfaceModeCount, PresentModes.data());

        for(const VkPresentModeKHR& Mode : PresentModes)
        {
            if(Mode == ModeTarget)
            {
                return Mode;
            }
        }
        return PresentModes[0];
    }

    EkWindow* CreateWindow(int Width, int Height, std::string AppName)
    {
        glfwInit();

        if(glfwVulkanSupported() != GLFW_TRUE)
        {
            ThrowError("GLFW: Vulkan Not Supported");
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        Window = glfwCreateWindow(Width, Height, AppName.c_str(), nullptr, nullptr);

        GlfwExts = glfwGetRequiredInstanceExtensions(&glfwExtCount);

        CleanupQueue([this](){ glfwDestroyWindow(Window); glfwTerminate(); std::cout << "Deleted and terminated glfwWindow\n"; });
        return this;
    }

    void CreateSurface(VkInstance* Instance)
    {
        VkResult Result = glfwCreateWindowSurface(*Instance, Window, nullptr, &Surface);
        if(Result != VK_SUCCESS)
        {
            std::cout << "Error: " << Result << std::endl;
            ThrowError("GLFW: Can't create window surface");
        }

        CleanupQueue([this, Instance](){ vkDestroySurfaceKHR(*Instance, Surface, nullptr); std::cout << "Deleted surface"; });
    }

    void CreateSwapchain(VkDevice* Device, uint32_t GraphicsFamilyIndex, VkPresentModeKHR PresentationMode)
    {
        VkSurfaceFormatKHR SurfaceFormat = QueryFormats(VK_FORMAT_R32G32B32_SFLOAT);

        VkSurfaceCapabilitiesKHR SurfaceCapabilites;
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(*PhysDevPtr, Surface, &SurfaceCapabilites);

        VkSwapchainCreateInfoKHR SwapchainInfo{};
        SwapchainInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        SwapchainInfo.surface = Surface;
        SwapchainInfo.presentMode = PresentationMode;
        SwapchainInfo.queueFamilyIndexCount = 1;
        SwapchainInfo.pQueueFamilyIndices = &GraphicsFamilyIndex;
        SwapchainInfo.minImageCount = BufferCount;

        SwapchainInfo.imageFormat = SurfaceFormat.format;
        SwapchainInfo.imageColorSpace = SurfaceFormat.colorSpace;
        SwapchainInfo.imageExtent = ImageExtents;
        SwapchainInfo.preTransform = SurfaceCapabilites.currentTransform;
        SwapchainInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        SwapchainInfo.clipped = VK_TRUE;

        if(vkCreateSwapchainKHR(*Device, &SwapchainInfo, nullptr, &Swapchain) != VK_SUCCESS)
        {
            ThrowError("failed to create a swapchain.");
        }

        vkGetSwapchainImagesKHR(*Device, Swapchain, &BufferCount, nullptr);
        SwapchainImages.resize(BufferCount);
        vkGetSwapchainImagesKHR(*Device, Swapchain, &BufferCount, SwapchainImages.data());

        CleanupQueue([Device, this](){ vkDeviceWaitIdle(*Device); vkDestroySwapchainKHR(*Device, Swapchain, nullptr); std::cout << "Deleted Swapchain\n"; });

        ImageFormat = SurfaceFormat.format;
    }

    void CreateFrameBuffers(VkDevice* DevicePtr, VkRenderPass* RenderPass)
    {
        ImageBuffers.resize(BufferCount);
        FrameBuffers.resize(BufferCount);

        std::vector<VkImageView> Attachments;
        
        for(const auto Attachment : ImageBuffers)
        {
            Attachments.push_back(Attachment.ImageView);
        }

        for(uint32_t i = 0; i < BufferCount; i++)
        {
            VkFramebufferCreateInfo FrameBufferInfo{};
            FrameBufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            FrameBufferInfo.renderPass = *RenderPass;
            FrameBufferInfo.attachmentCount = Attachments.size();
            FrameBufferInfo.pAttachments = Attachments.data();
            FrameBufferInfo.width = ImageExtents.width;
            FrameBufferInfo.height = ImageExtents.height;
            FrameBufferInfo.layers = 1;

            if(vkCreateFramebuffer(*DevicePtr, &FrameBufferInfo, nullptr, &FrameBuffers[i]) != VK_SUCCESS)
            {
                ThrowError("Failed to create a framebuffer");
            }
            VkFramebuffer* FBHandle = &FrameBuffers[i];
            CleanupQueue([DevicePtr, FBHandle](){ vkDestroyFramebuffer(*DevicePtr, *FBHandle, nullptr); std::cout << "Destroyed a framebuffer\n"; });
        }
    }


    private:
    std::vector<VkImage> SwapchainImages;
    VkFormat ImageFormat;

};

#endif