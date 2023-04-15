#include <Base/Instance.h>
#include <GLFW/glfw3.h>
#include <cstring>
#include <vulkan/vulkan_core.h>

void ThrowError(const char* ErrorMsg)
{
    throw std::runtime_error(ErrorMsg);
}

namespace Ek
{
    #ifdef GLFWAPP
        void Instance::CreateInstance(uint32_t VkVersion, const char* AppName)
        {
            glfwInit();

            uint32_t glfwExtCount = 0;
            const char **GLFWExtensions = glfwGetRequiredInstanceExtensions(&glfwExtCount);

            for (uint32_t i = 0; i < glfwExtCount; i++)
            {
                RequestInstanceExtension(GLFWExtensions[i]);
            }

            DelQueue([]{ glfwTerminate(); });

            Layers.shrink_to_fit();
            Extensions.shrink_to_fit();

            VkApplicationInfo AppInfo;
            AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            AppInfo.apiVersion = VkVersion;
            AppInfo.pEngineName = "EVK";
            AppInfo.engineVersion = 1;
            AppInfo.applicationVersion = 1;
            AppInfo.pApplicationName = AppName;

            VkInstanceCreateInfo InstCI{};
            InstCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            InstCI.enabledLayerCount = Layers.size();
            InstCI.ppEnabledLayerNames = Layers.data();
            InstCI.enabledExtensionCount = Extensions.size();
            InstCI.ppEnabledExtensionNames = Extensions.data();
            InstCI.pApplicationInfo = &AppInfo;

            VkResult Error = vkCreateInstance(&InstCI, nullptr, &VkInst);
            if(Error != VK_SUCCESS)
            {
                std::cout << Error << std::endl;
                ThrowError("Failed to create Instance");
            }

            VkInstance& LambdaInstance = VkInst;
            DelQueue( [&LambdaInstance](){ vkDestroyInstance(LambdaInstance, nullptr); } );
        }
    #else
        void Instance::CreateInstance(uint32_t VkVersion, const char* AppName)
        {
            Layers.shrink_to_fit();
            Extensions.shrink_to_fit();

            VkApplicationInfo AppInfo;
            AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            AppInfo.apiVersion = VkVersion;
            AppInfo.pEngineName = "EVK";
            AppInfo.engineVersion = 1;
            AppInfo.applicationVersion = 1;
            AppInfo.pApplicationName = AppName;

            VkInstanceCreateInfo InstCI{};
            InstCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            InstCI.enabledLayerCount = Layers.size();
            InstCI.ppEnabledLayerNames = Layers.data();
            InstCI.enabledExtensionCount = Extensions.size();
            InstCI.ppEnabledExtensionNames = Extensions.data();
            InstCI.pApplicationInfo = &AppInfo;

            VkResult Error = vkCreateInstance(&InstCI, nullptr, &VkInst);
            if(Error != VK_SUCCESS)
            {
                std::cout << Error << std::endl;
                ThrowError("Failed to create Instance");
            }

            VkInstance& LambdaInstance = VkInst;
            DelQueue( [&LambdaInstance](){ vkDestroyInstance(LambdaInstance, nullptr); } );
        }
    #endif

    bool Instance::CheckInstanceExtensionSupport(const char* ExtensionName, const char* ExtensionLayer)
    {
        uint32_t ExtCount = 0;
        vkEnumerateInstanceExtensionProperties(ExtensionLayer, &ExtCount, nullptr);

        std::vector<VkExtensionProperties> ExtProps(ExtCount);
        vkEnumerateInstanceExtensionProperties(ExtensionLayer, &ExtCount, ExtProps.data());

        for(const auto& ExtProp : ExtProps)
        {
            if(strcmp(ExtensionName, ExtProp.extensionName) == 0)
            {
                return true;
            }
        }
        return false;
    }

    bool Instance::CheckLayerSupport(const char* LayerName)
    {
        uint32_t LayerCount = 0;
        vkEnumerateInstanceLayerProperties(&LayerCount, nullptr);

        std::vector<VkLayerProperties> AvailableLayers(LayerCount);
        vkEnumerateInstanceLayerProperties(&LayerCount, AvailableLayers.data());

        for(int i = 0; i < AvailableLayers.size(); i++)
        {
            if(strcmp(LayerName, AvailableLayers[i].layerName) == 0)
            {
                return true;
            }
        }

        return false;
    }

    void Instance::RequestLayer(const char* LayerName)
    {
        if(CheckLayerSupport(LayerName))
        {
            Layers.push_back(LayerName);
            std::cout << "the layer " << LayerName << " is supported and is being loaded" << std::endl;
            return;
        }
        else
        {
            std::cout << "the layer " << LayerName << " is not supported and is will not be loaded" << std::endl;
        }
        return;
    }

    void Instance::RequestInstanceExtension(const char* ExtensionName)
    {
        if(CheckInstanceExtensionSupport(ExtensionName))
        {
            Extensions.push_back(ExtensionName);
            std::cout << "Extension " << ExtensionName << " is supported and is loading\n";
            return;
        }
        std::cout << "Extension " << ExtensionName << " isn't supported and will not be loaded\n";
    }
}
