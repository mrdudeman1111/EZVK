#ifdef GLFWAPP

#include <Base/EkWindow.hpp>

namespace Ek
{
    Window::Window()
    {
        const char** Extensions = glfwGetRequiredInstanceExtensions(&glfwExtCount);

        for(uint32_t i = 0; i < glfwExtCount; i++)
        {
            glfwExts.push_back(Extensions[i]);
        }
    }

    VkFormat EkWindow::QueryFormat()
    {
        uint32_t FormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, nullptr);

        std::vector<VkSurfaceFormatKHR> AvFormats(FormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, AvFormats.data());

        for(uint32_t i = 0; i < AvFormats.size(); i++)
        {
            std::cout << AvFormats[i].format << std::endl;
        }
    }

    void EkWindow::CreateSurface()
    {
        glfwCreateWindowSurface(Instance, Window, nullptr, &Surface);
    }

    void EkWindow::CreateWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwCreateWindow(Width, Height, WindowName, NULL, NULL);
    }
}

#endif
