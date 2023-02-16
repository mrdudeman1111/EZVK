#include <Base/EkHelpers.hpp>
#include <VkBootstrap.h>
#include <GLFW/glfw3.h>
#include <iomanip>

VkInstance Instance;
VkDevice GlobDevice;
VkPhysicalDevice PhysicalDevice;
VmaAllocator Allocator;
VkDebugUtilsMessengerEXT DebugMessenger;

DeleteQueue DeletionQueue;

void ThrowError(const char* Error)
{
    throw std::runtime_error(Error);
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

// Instance:

void EkVulkan::CreateInstance()
{
    #ifdef GLFWAPP
        Window = new Ek::Window();
        for(uint32_t i = 0; i < Window->glfwExtCount; i++)
        {
            RequestInstanceExtension(Window->glfwExts[i]);
        }
    #endif

    Layers.shrink_to_fit();
    Extensions.shrink_to_fit();

    VkInstanceCreateInfo InstCI{};
    InstCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    InstCI.enabledLayerCount = Layers.size();
    InstCI.ppEnabledLayerNames = Layers.data();
    InstCI.enabledExtensionCount = Extensions.size();
    InstCI.ppEnabledExtensionNames = Extensions.data();

    VkResult Error = vkCreateInstance(&InstCI, nullptr, &Instance);
    if(Error != VK_SUCCESS)
    {
        std::cout << Error << std::endl;
        ThrowError("Failed to create Instance");
    }

    VkInstance& LambdaInstance = Instance;
    DeletionQueue( [&LambdaInstance](){ vkDestroyInstance(LambdaInstance, nullptr); } );

    // VkDebugUtilsMessengerCreateInfoEXT DebugCI{};
    // DebugCI.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    // DebugCI.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    // DebugCI.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
    // DebugCI.pfnUserCallback = DebugCallback;

    // auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(Instance,"vkCreateDebugUtilsMessengerEXT");

    // if(func == nullptr)
    // {
    //     ThrowError("Failed to create debug utilities");
    // }

    // func(Instance, &DebugCI, nullptr, &DebugMessenger);




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
    // PhysicalDevice = vkbPDev.physical_device;

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


    bool EkVulkan::CheckInstanceExtensionSupport(const char* ExtensionName, const char* ExtensionLayer)
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

    bool EkVulkan::CheckLayerSupport(const char* LayerName)

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

    void EkVulkan::RequestLayer(const char* LayerName)
    {
        if(CheckLayerSupport(LayerName))
        {
            Layers.push_back(LayerName);
            std::cout << "the layer " << LayerName << " is supported and is being loaded" << std::endl;
            return;
        }
        std::cout << "the layer " << LayerName << " is not supported and is will not be loaded" << std::endl;
        return;
    }

    void EkVulkan::RequestInstanceExtension(const char* ExtensionName)
    {
        if(CheckInstanceExtensionSupport(ExtensionName))
        {
            Extensions.push_back(ExtensionName);
            std::cout << "Extension " << ExtensionName << " is supported and is loading\n";
            return;
        }
        std::cout << "Extension " << ExtensionName << " isn't supported and will not be loaded\n";
    }


// Device:


    bool EkVulkan::CheckDeviceExtensionSupport(const char* ExtensionName)
    {
        uint32_t ExtCount = 0;

        if(vkEnumerateDeviceExtensionProperties(PhysicalDevice, nullptr, &ExtCount, nullptr) != VK_SUCCESS)
        {
            Warn("can't enumerate Device extensions");
            return false;
        }

        std::vector<VkExtensionProperties> DeviceExtensions(ExtCount);
        
        if(vkEnumerateDeviceExtensionProperties(PhysicalDevice, nullptr, &ExtCount, nullptr) != VK_SUCCESS)
        {
            Warn("Can't enumerate device extensions");
            return false;
        }

        for(uint32_t i = 0; i < ExtCount; i++)
        {
            if(strcmp(DeviceExtensions[i].extensionName, ExtensionName))
            {
                return true;
            }
        }

        return false;
    }

    void EkVulkan::RequestDeviceExtension(const char* ExtensionName)
    {
        if(CheckDeviceExtensionSupport(ExtensionName))
        {
            DeviceExtensions.push_back(ExtensionName);
            std::cout << "Device extension " << ExtensionName << " is available\n";
        }
        std::cout << "Device extension " << ExtensionName << " is not available\n";
    }

bool EkVulkan::CheckDevice(VkPhysicalDevice* PhysicalDevice)
{
    VkPhysicalDeviceProperties DeviceProperties;
    vkGetPhysicalDeviceProperties(*PhysicalDevice, &DeviceProperties);

    VkPhysicalDeviceFeatures DeviceFeatures;
    vkGetPhysicalDeviceFeatures(*PhysicalDevice, &DeviceFeatures);

    if(DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        return true;
    }
    return false;
}


// Queues:
    void EkVulkan::ListQueueFamilies()
    {
        uint32_t QueueFamilyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyCount, QueueFamilies.data());

        for(uint32_t i = 0; i < QueueFamilies.size(); i++)
        {
            std::cout << "Queue at " << i << " Has ";
            std::cout << QueueFamilies[i].queueCount << " Queues and is a ";
            std::cout << QueueFamilies[i].queueFlags << " queue" << std::endl;
        }
    }

    void EkVulkan::FindQueueFamilies()
    {
        uint32_t QueueFamCount;
        vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamCount, nullptr);

        std::cout << "Found " << QueueFamCount << " QueueFamilies" << std::endl;

        std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamCount);
        vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamCount, QueueFamilies.data());

        for(uint32_t i = 0; i < QueueFamilies.size(); i++)
        {
            std::cout << "Parsing Queue type of : " << QueueFamilies[i].queueFlags << std::endl;

            if(QueueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                FamilyIndices.GraphicsFamily = i;
                std::cout << "Found Graphics Family\n";
            }

            else if(QueueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                FamilyIndices.ComputeFamily = i;
                std::cout << "Found Compute Family\n";
            }
            
            else if(QueueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                FamilyIndices.TransferFamily = i;
                std::cout << "Found Transfer Family\n";
            }

            else if(QueueFamilies[i].queueFlags & VK_QUEUE_PROTECTED_BIT)
            {
                FamilyIndices.ProtectedFamily = i;
                std::cout << "Found Protected Family\n";
            }
            
            #ifdef VK_ENABLE_BETA_EXTENSIONS
                else if(QueueFamilies[i].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR)
                {
                    FamilyIndices.DecodeFamily = i;
                    std::cout << "Found Decode Family\n";
                }

                else if(QueueFamilies[i].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR)
                {
                    FamilyIndices.EncodeFamily = i;
                    std::cout << "Found Encode Family\n";
                }
            #endif

            else
            {
                std::cout << "Failed to parse a queue" << std::endl;
            }

            // switch(QueueFamilies[i].queueFlags)
            // {
            //     case VK_QUEUE_GRAPHICS_BIT:
            //         FamilyIndices.GraphicsFamily = i;
            //         break;

            //     case VK_QUEUE_COMPUTE_BIT:
            //         FamilyIndices.ComputeFamily = i;
            //         break;

            //     case VK_QUEUE_TRANSFER_BIT:
            //         FamilyIndices.TransferFamily = i;
            //         break;

            //     case VK_QUEUE_PROTECTED_BIT:
            //         FamilyIndices.ProtectedFamily = i;
            //         break;

            //     #ifdef VK_ENABLE_BETA_EXTENSIONS

            //         case VK_QUEUE_VIDEO_ENCODE_BIT_KHR:
            //             FamilyIndices.EncodeFamily = i;
            //             break;

            //         case VK_QUEUE_VIDEO_DECODE_BIT_KHR:
            //             FamilyIndices.DecodeFamily = i;
            //             break;

            //     #endif
            //     default:
            //         ThrowError("Failed to parse queue");
            // }
        }
    }


void EkVulkan::InitVMA()
{
    VmaAllocatorCreateInfo AllocatorInfo = {};
    AllocatorInfo.instance = Instance;
    AllocatorInfo.physicalDevice = PhysicalDevice;
    AllocatorInfo.device = GlobDevice;
    vmaCreateAllocator(&AllocatorInfo, &Allocator);
}

void EkVulkan::PickPhysDev()
{
    uint32_t DeviceCount = 0;
    vkEnumeratePhysicalDevices(Instance, &DeviceCount, nullptr);

    std::vector<VkPhysicalDevice> Devices(DeviceCount);
    vkEnumeratePhysicalDevices(Instance, &DeviceCount, Devices.data());

    std::cout << "You have " << Devices.size() << " Physical Devices\n";

    if(DeviceCount == 0)
    {
        ThrowError("Failed to find Physical Device with vulkan support");
    }
    
    for(uint32_t i = 0; i < Devices.size(); i++) 
    {
        if(CheckDevice(&Devices[i])) 
        {
            PhysicalDevice = Devices[i];
            return;
        }
    }

    throw std::runtime_error("Failed to find supported PhysDev");
}

void EkVulkan::CreateDevice(std::vector<std::string>* DesiredQueues)
{
    // Fills FamilyIndices member, which contains the index for every queue family
    FindQueueFamilies();
    std::cout << "Family indices full" << std::endl;

    std::vector<VkDeviceQueueCreateInfo> QueueInfos;

    int GraphicsCount = 0;
    int ComputeCount = 0;
    int TransferCount = 0;
    int SparseBindCount = 0;
    int ProtectedCount = 0;
    int OpticFlowCount = 0;
    int DecodeCount = 0;
    int EncodeCount = 0;
    
    for(uint32_t i = 0; i < DesiredQueues->size(); i++)
    {
        if(DesiredQueues->at(i) == "graphics")
        {
            GraphicsCount++;
        }
        else if(DesiredQueues->at(i) == "compute")
        {
            ComputeCount++;
        }
        else if(DesiredQueues->at(i) == "transfer")
        {
            TransferCount++;
        }
        else if(DesiredQueues->at(i) == "sparse bind")
        {
            SparseBindCount++;
        }
        else if(DesiredQueues->at(i) == "protected")
        {
            ProtectedCount++;
        }
        else if(DesiredQueues->at(i) == "optic flow")
        {
            OpticFlowCount++;
        }
        #ifdef VK_ENABLE_BETA_EXTENSIONS
            else if(*DesiredQueues[i] == "decode")
            {
                DecodeCount++;
            }
            else if(*DesiredQueues[i] == "encode")
            {
                EncodeCount++;
            }
        #endif
    }

    if(GraphicsCount > 0)
    {
        VkDeviceQueueCreateInfo GraphicsQueueInfo{};
        GraphicsQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        GraphicsQueueInfo.queueFamilyIndex = FamilyIndices.GraphicsFamily;
        GraphicsQueueInfo.queueCount = GraphicsCount;
        std::cout << "Graphics Queue Info Pushed" << std::endl;
        QueueInfos.push_back(GraphicsQueueInfo);
    }

    if(ComputeCount > 0)
    {
        VkDeviceQueueCreateInfo ComputeQueueInfo{};
        ComputeQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        ComputeQueueInfo.queueFamilyIndex = FamilyIndices.ComputeFamily;
        ComputeQueueInfo.queueCount = ComputeCount;
        std::cout << "Compute Queue Info Pushed" << std::endl;
        QueueInfos.push_back(ComputeQueueInfo);
    }

    if(TransferCount > 0)
    {
        VkDeviceQueueCreateInfo TransferQueueInfo{};
        TransferQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        TransferQueueInfo.queueFamilyIndex = FamilyIndices.TransferFamily;
        TransferQueueInfo.queueCount = TransferCount;
        std::cout << "Transfer Queue Info Pushed" << std::endl;
        QueueInfos.push_back(TransferQueueInfo);
    }

    if(SparseBindCount > 0)
    {
        VkDeviceQueueCreateInfo SparseBindQueueInfo{};
        SparseBindQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        SparseBindQueueInfo.queueFamilyIndex = FamilyIndices.SparseBindingFamily;
        SparseBindQueueInfo.queueCount = SparseBindCount;
        std::cout << "Sparse Bind Queue Info Pushed" << std::endl;
        QueueInfos.push_back(SparseBindQueueInfo);
    }

    if(ProtectedCount > 0)
    {
        VkDeviceQueueCreateInfo ProtectedQueueInfo{};
        ProtectedQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        ProtectedQueueInfo.queueFamilyIndex = FamilyIndices.ProtectedFamily;
        ProtectedQueueInfo.queueCount = ProtectedCount;
        std::cout << "Protected Queue Info Pushed" << std::endl;
        QueueInfos.push_back(ProtectedQueueInfo);
    }

    if(OpticFlowCount > 0)
    {
        VkDeviceQueueCreateInfo OpticFlowQueueInfo{};
        OpticFlowQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        OpticFlowQueueInfo.queueFamilyIndex = FamilyIndices.OpticFlowFamily;
        OpticFlowQueueInfo.queueCount = OpticFlowCount;
        std::cout << "Optic Flow Queue Info Pushed" << std::endl;
        QueueInfos.push_back(OpticFlowQueueInfo);
    }

    #ifdef VK_ENABLE_BETA_EXTENSIONS
        if(DecodeCount > 0)
        {
            VkDeviceQueueCreateInfo DecodeQueueInfo{};
            DecodeQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            DecodeQueueInfo.queueFamilyIndex = FamilyIndices.DecodeFamily;
            DecodeQueueInfo.queueCount = DecodeCount;
            std::cout << "Decode Queue Info Pushed" << std::endl;
            QueueInfos.push_back(DecodeQueueInfo);
        }

        if(EncodeCount > 0)
        {
            VkDeviceQueueCreateInfo EncodeQueueInfo{};
            EncodeQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            EncodeQueueInfo.queueFamilyIndex = FamilyIndices.EncodeFamily;
            EncodeQueueInfo.queueCount = EncodeCount;
            std::cout << "Encode Queue Info Pushed" << std::endl;   
            QueueInfos.push_back(EncodeQueueInfo);
        }
    #endif

    VkPhysicalDeviceFeatures DeviceFeatures;
    vkGetPhysicalDeviceFeatures(PhysicalDevice, &DeviceFeatures);

    VkDeviceCreateInfo DevInfo{};
    DevInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    
    DevInfo.queueCreateInfoCount = QueueInfos.size();
    DevInfo.pQueueCreateInfos = QueueInfos.data();

    DevInfo.pEnabledFeatures = &DeviceFeatures;

    DevInfo.enabledExtensionCount = DeviceExtensions.size();
    DevInfo.ppEnabledExtensionNames = DeviceExtensions.data();

    if(vkCreateDevice(PhysicalDevice, &DevInfo, nullptr, &GlobDevice) != VK_SUCCESS)
    {
        ThrowError("Failed to create Device");
    }


    GraphicsQueues.resize(GraphicsCount);
    ComputeQueues.resize(ComputeCount);
    TransferQueues.resize(TransferCount);
    SparseBindingQueues.resize(SparseBindCount);
    ProtectedQueues.resize(ProtectedCount);
    OpticFlowQueues.resize(OpticFlowCount);
    #ifdef VK_ENABLE_BETA_EXTENSIONS
        DecodeQueues.resize(DecodeCount);
        EncodeQueues.resize(EncodeCount);
    #endif

    for(int i = 0; i < GraphicsCount; i++)
    {
        vkGetDeviceQueue(GlobDevice, FamilyIndices.GraphicsFamily, i, &(GraphicsQueues[i].VulkanQueue));
    }

    for(int i = 0; i < ComputeCount; i++)
    {
        vkGetDeviceQueue(GlobDevice, FamilyIndices.ComputeFamily, i, &ComputeQueues[i].VulkanQueue);
    }

    for(int i = 0; i < TransferCount; i++)
    {
        vkGetDeviceQueue(GlobDevice, FamilyIndices.TransferFamily, i, &TransferQueues[i].VulkanQueue);
    }
    
    for(int i = 0; i < SparseBindCount; i++)
    {
        vkGetDeviceQueue(GlobDevice, FamilyIndices.SparseBindingFamily, i, &SparseBindingQueues[i].VulkanQueue);
    }

    for(int i = 0; i < ProtectedCount; i++)
    {
        vkGetDeviceQueue(GlobDevice, FamilyIndices.ProtectedFamily, i, &ProtectedQueues[i].VulkanQueue);
    }

    for(int i = 0; i < OpticFlowCount; i++)
    {
        vkGetDeviceQueue(GlobDevice, FamilyIndices.OpticFlowFamily, i, &ProtectedQueues[i].VulkanQueue);
    }
    
    #ifdef VK_ENABLE_BETA_EXTENSIONS
        for(int i = 0; i < DecodeCount; i++)
        {
            vkGetDeviceQueue(GlobDevice, FamilyIndices.DecodeFamily, i, &DecodeQueues[i].VulkanQueue);
        }

        for(int i = 0; i < EncodeCount; i++)
        {
            vkGetDeviceQueue(GlobDevice, FamilyIndices.EncodeCount, i, &EncodeQueues[i].VulkanQueue);
        }
    #endif

    DeletionQueue([this](){ vkDestroyDevice(GlobDevice, nullptr); });
}

// Queue Type is a string indicating what type of queue you are using, Options are graphics, compute, transfer, "sparse bind", protected, "optic flow", decode, and encode
EkCmdPool* EkVulkan::CreateCommandPool(std::string QueueType)
{
    if(QueueType == "graphics")
    {
        EkCmdPool* Pool = new EkCmdPool(FamilyIndices.GraphicsFamily, &DeletionQueue);
        DeletionQueue([Pool](){ delete Pool; });
        return Pool;
    }
    else if(QueueType == "compute")
    {
        EkCmdPool* Pool = new EkCmdPool(FamilyIndices.ComputeFamily, &DeletionQueue);
        DeletionQueue([Pool](){ delete Pool; });
        return Pool;
    }
    else if(QueueType == "transfer")
    {
        EkCmdPool* Pool = new EkCmdPool(FamilyIndices.TransferFamily, &DeletionQueue);
        DeletionQueue([Pool](){ delete Pool; });
        return Pool;
    }
    else if(QueueType == "sparse bind")
    {
        EkCmdPool* Pool = new EkCmdPool(FamilyIndices.SparseBindingFamily, &DeletionQueue);
        DeletionQueue([Pool](){ delete Pool; });
        return Pool;
    }
    else if(QueueType == "protected")
    {
        EkCmdPool* Pool = new EkCmdPool(FamilyIndices.ProtectedFamily, &DeletionQueue);
        DeletionQueue([Pool](){ delete Pool; });
        return Pool;
    }
    else if(QueueType == "optic flow")
    {
        EkCmdPool* Pool = new EkCmdPool(FamilyIndices.OpticFlowFamily, &DeletionQueue);
        DeletionQueue([Pool](){ delete Pool; });
        return Pool;
    }
    #ifdef VK_ENABLE_BETA_EXTENSIONS
        else(QueueType == "decode")
        {
            EkCmdPool* Pool = new EkCmdPool(FamilyIndices.DecodeFamily, &DeletionQueue);
            DeletionQueue([Pool](){ delete Pool; });
            return Pool;
        }
        else(QueueType == "encode")
        {
            EkCmdPool* Pool = new EkCmdPool(FamilyIndices.EncodeFamily, &DeletionQueue);
            DeletionQueue([Pool](){ delete Pool; });
            return &Pool;
        }
    #endif
    ThrowError("Failed to create CommandPool");
}

#ifdef GLFWAPP
    Ek::Window* EkVulkan::CreateWindow(int Width, int Height, const char* AppName)
    {
        Window->CreateWindow(Width, Height, "Vulkan wrapper tester");
        Window->CreateSurface();
        Window->PresentFamily = FamilyIndices.GraphicsFamily;
        return Window;
    }
#endif
