#include <EkHelpers.hpp>
#include <VkBootstrap.h>

// Vulkan Basics
    VkInstance Instance;
    VkPhysicalDevice PhysDev;
    VkDevice Device;
    std::vector<const char*> Layers;
    std::vector<const char*> Extensions;
    const char** GlfwExts;

// Vma stuff
    VmaAllocator Allocator;

// Vulkan Queues
    VkQueue GraphicsQueue;
    VkQueue PresentQueue;
    int GraphicsQueueFamilyIndex;

// Window Stuff
    GLFWwindow* Window;
    int Width = 1280;
    int Height = 720;
    VkSurfaceKHR Surface;

void ThrowError(const char* Error)
{
    throw std::runtime_error(Error);
}

namespace Buffers
{
    void CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, AllocatedBuffer* AllocatedBuffer, VmaMemoryUsage MemUse)
    {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = Size;
        bufferInfo.usage = Usage;

        VmaAllocationCreateInfo VmaAllocateCreateInfo = {};
        VmaAllocateCreateInfo.usage = MemUse;

        if(auto res = vmaCreateBuffer(Allocator, &bufferInfo, &VmaAllocateCreateInfo, &AllocatedBuffer->Buffer, &AllocatedBuffer->Allocation, nullptr) != VK_SUCCESS)
        {
            std::cerr << "Error: " << res << std::endl; 
            throw std::runtime_error("Failed to create a buffer");
        }
    }
}

namespace Mesh
{
    // glm::mat4 ConvertMat4(aiMatrix4x4 AssimpMatrix)
    // {
    //     glm::mat4 Result
    //     (
    //         AssimpMatrix[0][0], AssimpMatrix[3][1], AssimpMatrix[3][2], AssimpMatrix[0][3],
    //         AssimpMatrix[1][0], AssimpMatrix[2][1], AssimpMatrix[2][2], AssimpMatrix[1][3],
    //         AssimpMatrix[2][0], AssimpMatrix[1][1], AssimpMatrix[1][2], AssimpMatrix[2][3],
    //         AssimpMatrix[3][0], AssimpMatrix[0][1], AssimpMatrix[0][2], AssimpMatrix[3][3]
    //     );
    //     return Result;
    // }
}

namespace InitHelpers
{
    bool CheckDevice(VkPhysicalDevice* Device)
    {
        VkPhysicalDeviceProperties DeviceProperties;
        vkGetPhysicalDeviceProperties(*Device, &DeviceProperties);

        VkPhysicalDeviceFeatures DeviceFeatures;
        vkGetPhysicalDeviceFeatures(*Device, &DeviceFeatures);

        return true;

        std::cout << DeviceProperties.apiVersion;
    }

    void InitGlfw()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        Window = glfwCreateWindow(Width, Height, "Vulkan Renderer", nullptr, nullptr);

        uint32_t glfwExtCount = 0;
        GlfwExts = glfwGetRequiredInstanceExtensions(&glfwExtCount);

        if(glfwVulkanSupported() != GLFW_TRUE)
        {
            throw std::runtime_error("vulkan is not supported for glfw");
        }
    }

    void RequestLayer(const char* LayerName)
    {
        Layers.push_back(LayerName);
    }

    void RequestExtension(const char* ExtensionName)
    {
        Extensions.push_back(ExtensionName);
    }

    void InitVMA()
    {
	    VmaAllocatorCreateInfo AllocatorInfo = {};
	    AllocatorInfo.physicalDevice = PhysDev;
	    AllocatorInfo.device = Device;
	    AllocatorInfo.instance = Instance;
	    vmaCreateAllocator(&AllocatorInfo, &Allocator);
    }

    void CreateInstance()
    {
        VkInstanceCreateInfo InstCI{};
        InstCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        InstCI.enabledLayerCount = Layers.size();
        InstCI.ppEnabledLayerNames = Layers.data();
        InstCI.enabledExtensionCount = Extensions.size();
        InstCI.ppEnabledExtensionNames = Extensions.data();

        if(vkCreateInstance(&InstCI, nullptr, &Instance) != VK_SUCCESS)
        {
            ThrowError("Failed to create Instance");
        }






        // vkb::InstanceBuilder instance_builder;
        // instance_builder.request_validation_layers(true);

        // instance_builder.set_debug_callback (
        // [] (VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        //     VkDebugUtilsMessageTypeFlagsEXT messageType,
        //     const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        //     void *pUserData) 
        // -> VkBool32 {
        //                 auto severity = vkb::to_string_message_severity (messageSeverity);
        //                 auto type = vkb::to_string_message_type (messageType);
        //                 printf ("[%s: %s] %s\n", severity, type, pCallbackData->pMessage);
        //                 return VK_FALSE;
        //             }
        //     );

        // auto system_info_ret = vkb::SystemInfo::get_system_info();
        // if (!system_info_ret) 
        // {
        //         printf("%s\n", system_info_ret.error().message());
        //         throw std::runtime_error("failed to get system Info");
        // }

        // auto system_info = system_info_ret.value();

        // for(uint16_t i = 0; i < Layers.size())
        // {
        //     if(system_info.is_layer_available(Layers[i]))
        //     {
        //         instance_builder.enable_layer(Layers[i]);
        //     }
        // }

        // for(uint16_t i = 0; i < Extensions.size())
        // {
        //     if(system_info.is_extension_available(Extensions[i]))
        //     {
        //         instance_builder.enable_extension(Extensions[i]);
        //     }
        // }

        // auto instance_ret = instance_builder.require_api_version(1,2,0).build();

        // if(!instance_ret)
        // {
        //     std::cout << instance_ret.error().message() << "\n";
        // }

        // vkb::Instance vkbInst = instance_ret.value();
        // Instance = vkbInst.instance;

        // vkb::PhysicalDeviceSelector PhysDevSelector(vkbInst);
        // auto PhysDevResult = PhysDevSelector.set_surface(Surface).select();
        // if(!PhysDevResult)
        // {
        //     std::cout << "Physical Device selector failed with an error message saying: " << PhysDevResult.error().message() << "\n";
        // }
        // vkb::PhysicalDevice vkbPDev = PhysDevResult.value();
        // PhysDev = vkbPDev.physical_device;

        // vkb::DeviceBuilder DevBuilder{ vkbPDev };
        // auto DeviceResult = DevBuilder.build();
        // if(!DeviceResult)
        // {
        //     std::cout << "Device Creation failed" << DeviceResult.error().message() << std::endl;
        // }
        // vkbDevice = DeviceResult.value();
        // VkDevice Device = vkbDevice.device;
        // GraphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
        // PresentQueue = vkbDevice.get_queue(vkb::QueueType::present).value();
        // GraphicsQueueFamilyIndex = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();
    }

    void PickPhysDev()
    {
        uint32_t DeviceCount = 0;
        vkEnumeratePhysicalDevices(Instance, &DeviceCount, nullptr);

        if(DeviceCount == 0);
        {
            ThrowError("Failed to find a gpu with vulkan support");
        }

        std::vector<VkPhysicalDevice> Devices(DeviceCount);
        vkEnumeratePhysicalDevices(Instance, &DeviceCount, Devices.data());

        for (auto Device : Devices) 
        {
            if (CheckDevice(&Device)) 
            {
                PhysDev = Device;
                break;
            }
        }

        if (PhysDev == VK_NULL_HANDLE) 
        {
            ThrowError("Physical Device is invalid");
        }
    }

    void CreateSwapChain(VkDevice* Device, VkInstance* Instance)
    {
        // VkSwapchainCreateInfoKHR
    }
}
