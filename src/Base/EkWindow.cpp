#ifdef GLFWAPP

#include <Base/EkWindow.hpp>

extern VkInstance Instance;
extern VkPhysicalDevice PhysicalDevice;
extern DeleteQueue DeletionQueue;

namespace Ek
{
    Window::Window()
    {
        glfwInit();

        const char** Extensions = glfwGetRequiredInstanceExtensions(&glfwExtCount);

        for(uint32_t i = 0; i < glfwExtCount; i++)
        {
            glfwExts.push_back(Extensions[i]);
        }

        DeletionQueue([]{ glfwTerminate(); });
    }

    VkFormat Window::QueryFormats()
    {
        uint32_t FormatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, nullptr);

        std::vector<VkSurfaceFormatKHR> AvFormats(FormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(PhysicalDevice, Surface, &FormatCount, AvFormats.data());

        for(uint32_t i = 0; i < FormatCount; i++)
        {
            std::cout << AvFormats[i].format << std::endl;
        }

        return VK_FORMAT_R32G32B32A32_SFLOAT;
    }

    void Window::CreateSurface()
    {
        VkResult Res = glfwCreateWindowSurface(Instance, glfwWindow, nullptr, &Surface);

        if(Res != VK_SUCCESS)
        {
            std::cout << "Failed to create Window Surface: " << Res << std::endl;
            throw std::runtime_error("Failed to Create surface");
        }

        VkInstance* InstanceHandle = &Instance;
        VkSurfaceKHR* SurfaceHandle = &Surface;
        DeletionQueue([InstanceHandle, SurfaceHandle]{ vkDestroySurfaceKHR(*InstanceHandle, *SurfaceHandle, nullptr); });
    }

    void Window::CreateWindow(int Width, int Height, const char* WindowName)
    {
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        glfwWindow = glfwCreateWindow(Width, Height, WindowName, nullptr, nullptr);

        GLFWwindow* WindowHandle = glfwWindow;

        DeletionQueue([WindowHandle]{ glfwDestroyWindow(WindowHandle); });
    }
}

#endif
