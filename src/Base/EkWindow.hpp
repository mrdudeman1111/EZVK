#pragma once

#include <Images/EkImages.hpp>
#include <Rendering/EkRenderpass.hpp>

#ifdef GLFWAPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <optional>

namespace Ek
{
    class Window
    {

        public:
        Window();
        Window(struct Device* Device, VkInstance* Instance, VkPhysicalDevice* PhysDev, VkQueue* PresentQueue) : pDev{Device}, pInst{Instance}, pPhysicalDevice{PhysDev}, pPresentQueue{PresentQueue}
        {}

        std::vector<FrameBuffer*> FrameBuffers;
        uint32_t glfwExtCount = 0;
        GLFWwindow* glfwWindow;
        std::vector<const char*> glfwExts;
        VkExtent3D WindowExtent;


        void CreateWindow(int Width, int Height, const char* WindowName);

        void CreateSurface();

        void CreateSwapchain(uint32_t DesiredFBCount);

        FrameBuffer* GetNextFrame(VkSemaphore* WaitSemaphore = nullptr, VkFence* Fence = nullptr);

        void cmdPresentFrame(uint32_t WaitSemaphoreCount = 0, VkSemaphore* WaitSemaphores = nullptr);

        private:

        VkPhysicalDevice* pPhysicalDevice;
        VkInstance* pInst;
        Device* pDev;
        VkQueue* pPresentQueue;

            VkSwapchainKHR Swapchain;
            VkSurfaceKHR Surface;

            VkSurfaceFormatKHR SurfaceFormat;
            uint32_t PresentFamily;
            uint32_t CurrentFrameIndex;

        private:

        void QueryFormats();

    };
}

#endif
