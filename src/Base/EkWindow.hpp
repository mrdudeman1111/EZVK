#ifdef GLFWAPP

#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Images/EkImages.hpp>
#include <Base/EkTypes.hpp>
#include <Rendering/EkRenderpass.hpp>

extern VkInstance Instance;
extern VkPhysicalDevice PhysicalDevice;

namespace Ek
{
    class Window
    {
        public:
            GLFWwindow* glfwWindow;
            VkSwapchainKHR Swapchain;
            VkSurfaceKHR Surface;
            std::vector<FrameBuffer> FrameBuffers;
            uint32_t glfwExtCount = 0;
            std::vector<const char*> glfwExts;

            VkSurfaceFormatKHR SurfaceFormat;
            int WindowHeight, WindowWidth;
            uint32_t PresentFamily;

        Window();

        void QueryFormats();

        void CreateSurface();

        void CreateWindow(int Width, int Height, const char* WindowName);

        void CreateSwapchain(uint32_t DesiredFBCount);

    };
}

#endif
