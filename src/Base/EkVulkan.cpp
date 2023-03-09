#include <Base/EkVulkan.hpp>
// #include <GLFW/glfw3.h>
// #include <iomanip>
// #include <cstring>

DeleteQueue DelQueue;

// void ThrowError(const char* Error)
// {
//     throw std::runtime_error(Error);
// }

// namespace Mesh
// {
//     // glm::mat4 ConvertMat4(aiMatrix4x4 AssimpMatrix)
//     // {
//     //     glm::mat4 Result
//     //     (
//     //         AssimpMatrix[0][0], AssimpMatrix[3][1], AssimpMatrix[3][2], AssimpMatrix[0][3],
//     //         AssimpMatrix[1][0], AssimpMatrix[2][1], AssimpMatrix[2][2], AssimpMatrix[1][3],
//     //         AssimpMatrix[2][0], AssimpMatrix[1][1], AssimpMatrix[1][2], AssimpMatrix[2][3],
//     //         AssimpMatrix[3][0], AssimpMatrix[0][1], AssimpMatrix[0][2], AssimpMatrix[3][3]
//     //     );
//     //     return Result;
//     // }
// }

// // Instance:

// namespace Ek
// {
//     #ifdef GLFWAPP
//         void Instance::CreateInstance()
//         {
//             glfwInit();

//             uint32_t glfwExtCount = 0;
//             const char **GLFWExtensions = glfwGetRequiredInstanceExtensions(&glfwExtCount);

//             for (uint32_t i = 0; i < glfwExtCount; i++)
//             {
//                 RequestInstanceExtension(GLFWExtensions[i]);
//             }

//             DelQueue([]{ glfwTerminate(); });

//             Layers.shrink_to_fit();
//             Extensions.shrink_to_fit();

//             VkInstanceCreateInfo InstCI{};
//             InstCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//             InstCI.enabledLayerCount = Layers.size();
//             InstCI.ppEnabledLayerNames = Layers.data();
//             InstCI.enabledExtensionCount = Extensions.size();
//             InstCI.ppEnabledExtensionNames = Extensions.data();

//             VkResult Error = vkCreateInstance(&InstCI, nullptr, &VkInst);
//             if(Error != VK_SUCCESS)
//             {
//                 std::cout << Error << std::endl;
//                 ThrowError("Failed to create Instance");
//             }

//             VkInstance& LambdaInstance = VkInst;
//             DelQueue( [&LambdaInstance](){ vkDestroyInstance(LambdaInstance, nullptr); } );
//         }
//     #else
//         void Instance::CreateInstance()
//         {
//             Layers.shrink_to_fit();
//             Extensions.shrink_to_fit();

//             VkInstanceCreateInfo InstCI{};
//             InstCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
//             InstCI.enabledLayerCount = Layers.size();
//             InstCI.ppEnabledLayerNames = Layers.data();
//             InstCI.enabledExtensionCount = Extensions.size();
//             InstCI.ppEnabledExtensionNames = Extensions.data();

//             VkResult Error = vkCreateInstance(&InstCI, nullptr, &Instance);
//             if(Error != VK_SUCCESS)
//             {
//                 std::cout << Error << std::endl;
//                 ThrowError("Failed to create Instance");
//             }

//             VkInstance& LambdaInstance = Instance;
//             DelQueue( [&LambdaInstance](){ vkDestroyInstance(LambdaInstance, nullptr); } );
//         }
//     #endif

//         bool Instance::CheckInstanceExtensionSupport(const char* ExtensionName, const char* ExtensionLayer)
//         {
//             uint32_t ExtCount = 0;
//             vkEnumerateInstanceExtensionProperties(ExtensionLayer, &ExtCount, nullptr);

//             std::vector<VkExtensionProperties> ExtProps(ExtCount);
//             vkEnumerateInstanceExtensionProperties(ExtensionLayer, &ExtCount, ExtProps.data());

//             for(const auto& ExtProp : ExtProps)
//             {
//                 if(strcmp(ExtensionName, ExtProp.extensionName) == 0)
//                 {
//                     return true;
//                 }
//             }
//             return false;
//         }

//         bool Instance::CheckLayerSupport(const char* LayerName)

//         {
//             uint32_t LayerCount = 0;
//             vkEnumerateInstanceLayerProperties(&LayerCount, nullptr);

//             std::vector<VkLayerProperties> AvailableLayers(LayerCount);
//             vkEnumerateInstanceLayerProperties(&LayerCount, AvailableLayers.data());

//             for(int i = 0; i < AvailableLayers.size(); i++)
//             {
//                 if(strcmp(LayerName, AvailableLayers[i].layerName) == 0)
//                 {
//                     return true;
//                 }
//             }

//             return false;
//         }

//         void Instance::RequestLayer(const char* LayerName)
//         {
//             if(CheckLayerSupport(LayerName))
//             {
//                 Layers.push_back(LayerName);
//                 std::cout << "the layer " << LayerName << " is supported and is being loaded" << std::endl;
//                 return;
//             }
//             std::cout << "the layer " << LayerName << " is not supported and is will not be loaded" << std::endl;
//             return;
//         }

//         void Instance::RequestInstanceExtension(const char* ExtensionName)
//         {
//             if(CheckInstanceExtensionSupport(ExtensionName))
//             {
//                 Extensions.push_back(ExtensionName);
//                 std::cout << "Extension " << ExtensionName << " is supported and is loading\n";
//                 return;
//             }
//             std::cout << "Extension " << ExtensionName << " isn't supported and will not be loaded\n";
//         }


//     // Physical Device:
//         bool PhysicalDevice::CheckDevice(VkPhysicalDevice* PhysicalDevice)
//         {
//             VkPhysicalDeviceProperties DeviceProperties;
//             vkGetPhysicalDeviceProperties(*PhysicalDevice, &DeviceProperties);

//             VkPhysicalDeviceFeatures DeviceFeatures;
//             vkGetPhysicalDeviceFeatures(*PhysicalDevice, &DeviceFeatures);

//             if(DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
//             {
//                 return true;
//             }
//             return false;
//         }

//     void PhysicalDevice::PickPhysDev(Instance* Instance)
//     {
//         uint32_t DeviceCount = 0;
//         vkEnumeratePhysicalDevices(Instance->VkInst, &DeviceCount, nullptr);

//         std::vector<VkPhysicalDevice> Devices(DeviceCount);
//         vkEnumeratePhysicalDevices(Instance->VkInst, &DeviceCount, Devices.data());

//         std::cout << "You have " << Devices.size() << " Physical Devices\n";

//         if(DeviceCount == 0)
//         {
//             ThrowError("Failed to find Physical Device with vulkan support");
//         }
        
//         for(uint32_t i = 0; i < Devices.size(); i++) 
//         {
//             if(CheckDevice(&Devices[i])) 
//             {
//                 VkPhysDev = Devices[i];
//                 return;
//             }
//         }

//         throw std::runtime_error("Failed to find supported PhysDev");
//     }

//     // Device:


//         bool Device::CheckDeviceExtensionSupport(const char* ExtensionName)
//         {
//             uint32_t ExtCount = 0;

//             if(vkEnumerateDeviceExtensionProperties(*PDev, nullptr, &ExtCount, nullptr) != VK_SUCCESS)
//             {
//                 Warn("can't enumerate Device extensions");
//                 return false;
//             }

//             std::vector<VkExtensionProperties> DeviceExtensions(ExtCount);
            
//             if(vkEnumerateDeviceExtensionProperties(*PDev, nullptr, &ExtCount, nullptr) != VK_SUCCESS)
//             {
//                 Warn("Can't enumerate device extensions");
//                 return false;
//             }

//             for(uint32_t i = 0; i < ExtCount; i++)
//             {
//                 if(strcmp(DeviceExtensions[i].extensionName, ExtensionName))
//                 {
//                     return true;
//                 }
//             }

//             return false;
//         }

//         void Device::RequestExtension(const char* ExtensionName)
//         {
//             if(CheckDeviceExtensionSupport(ExtensionName))
//             {
//                 DeviceExtensions.push_back(ExtensionName);
//                 std::cout << "Device extension " << ExtensionName << " is available\n";
//             }
//             std::cout << "Device extension " << ExtensionName << " is not available\n";
//         }

//         void Device::ListQueueFamilies()
//         {
//             uint32_t QueueFamilyCount;
//             vkGetPhysicalDeviceQueueFamilyProperties(*PDev, &QueueFamilyCount, nullptr);

//             std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
//             vkGetPhysicalDeviceQueueFamilyProperties(*PDev, &QueueFamilyCount, QueueFamilies.data());

//             for(uint32_t i = 0; i < QueueFamilies.size(); i++)
//             {
//                 std::cout << "Queue at " << i << " Has ";
//                 std::cout << QueueFamilies[i].queueCount << " Queues and is a ";
//                 std::cout << QueueFamilies[i].queueFlags << " queue" << std::endl;
//             }
//         }

//         void Device::FindQueueFamilies()
//         {
//             uint32_t QueueFamCount;
//             vkGetPhysicalDeviceQueueFamilyProperties(*PDev, &QueueFamCount, nullptr);

//             std::cout << "Found " << QueueFamCount << " QueueFamilies" << std::endl;

//             std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamCount);
//             vkGetPhysicalDeviceQueueFamilyProperties(*PDev, &QueueFamCount, QueueFamilies.data());

//             for(uint32_t i = 0; i < QueueFamilies.size(); i++)
//             {
//                 std::cout << "Parsing Queue type of : " << QueueFamilies[i].queueFlags << std::endl;

//                 if(QueueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
//                 {
//                     FamilyIndices.GraphicsFamily = i;
//                     std::cout << "Found Graphics Family\n";
//                 }

//                 else if(QueueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
//                 {
//                     FamilyIndices.ComputeFamily = i;
//                     std::cout << "Found Compute Family\n";
//                 }
                
//                 else if(QueueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
//                 {
//                     FamilyIndices.TransferFamily = i;
//                     std::cout << "Found Transfer Family\n";
//                 }

//                 else if(QueueFamilies[i].queueFlags & VK_QUEUE_PROTECTED_BIT)
//                 {
//                     FamilyIndices.ProtectedFamily = i;
//                     std::cout << "Found Protected Family\n";
//                 }
                
//                 #ifdef VK_ENABLE_BETA_EXTENSIONS
//                     else if(QueueFamilies[i].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR)
//                     {
//                         FamilyIndices.DecodeFamily = i;
//                         std::cout << "Found Decode Family\n";
//                     }

//                     else if(QueueFamilies[i].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR)
//                     {
//                         FamilyIndices.EncodeFamily = i;
//                         std::cout << "Found Encode Family\n";
//                     }
//                 #endif

//                 else
//                 {
//                     std::cout << "Failed to parse a queue" << std::endl;
//                 }
//             }
//         }

//         Window* Device::CreateWindow()
//         {
//             Window* Win = new Ek::Window();
//             Win->Create(PInstance, &VkDev, PDev);
//             return Win;
//         }

//     void Device::InitVMA()
//     {
//         VmaAllocatorCreateInfo AllocatorInfo = {};
//         AllocatorInfo.instance = *PInstance;
//         AllocatorInfo.physicalDevice = *PDev;
//         AllocatorInfo.device = VkDev;
//         vmaCreateAllocator(&AllocatorInfo, &Allocator);
//     }

//     void Device::Create(Instance* Inst, PhysicalDevice* PDevice, QueueList DesiredQueues)
//     {
//         PDev = &PDevice->VkPhysDev;
//         PInstance = &Inst->VkInst;

//         // Fills FamilyIndices member, which contains the index for every queue family
//         FindQueueFamilies();
//         std::cout << "Family indices full" << std::endl;

//         std::vector<VkDeviceQueueCreateInfo> QueueInfos;

//         int GraphicsCount = DesiredQueues[QueueType::Graphics];
//         int ComputeCount = DesiredQueues[QueueType::Compute];
//         int TransferCount = DesiredQueues[QueueType::Transfer];
//         int SparseBindCount = DesiredQueues[QueueType::SparseBind];
//         int ProtectedCount = DesiredQueues[QueueType::Protected];
//         int OpticFlowCount = DesiredQueues[QueueType::OpticFlow];

//         #ifdef VK_ENABLE_BETA_EXTENSIONS
//             int DecodeCount = DesiredQueues[QueueType::Decode];
//             int EncodeCount = DesiredQueues[QueueType::Encode];
//         #endif

//         if(GraphicsCount > 0)
//         {
//             VkDeviceQueueCreateInfo GraphicsQueueInfo{};
//             GraphicsQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//             GraphicsQueueInfo.queueFamilyIndex = FamilyIndices.GraphicsFamily;
//             GraphicsQueueInfo.queueCount = GraphicsCount;
//             std::cout << "Graphics Queue Info Pushed" << std::endl;
//             QueueInfos.push_back(GraphicsQueueInfo);
//         }

//         if(ComputeCount > 0)
//         {
//             VkDeviceQueueCreateInfo ComputeQueueInfo{};
//             ComputeQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//             ComputeQueueInfo.queueFamilyIndex = FamilyIndices.ComputeFamily;
//             ComputeQueueInfo.queueCount = ComputeCount;
//             std::cout << "Compute Queue Info Pushed" << std::endl;
//             QueueInfos.push_back(ComputeQueueInfo);
//         }

//         if(TransferCount > 0)
//         {
//             VkDeviceQueueCreateInfo TransferQueueInfo{};
//             TransferQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//             TransferQueueInfo.queueFamilyIndex = FamilyIndices.TransferFamily;
//             TransferQueueInfo.queueCount = TransferCount;
//             std::cout << "Transfer Queue Info Pushed" << std::endl;
//             QueueInfos.push_back(TransferQueueInfo);
//         }

//         if(SparseBindCount > 0)
//         {
//             VkDeviceQueueCreateInfo SparseBindQueueInfo{};
//             SparseBindQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//             SparseBindQueueInfo.queueFamilyIndex = FamilyIndices.SparseBindingFamily;
//             SparseBindQueueInfo.queueCount = SparseBindCount;
//             std::cout << "Sparse Bind Queue Info Pushed" << std::endl;
//             QueueInfos.push_back(SparseBindQueueInfo);
//         }

//         if(ProtectedCount > 0)
//         {
//             VkDeviceQueueCreateInfo ProtectedQueueInfo{};
//             ProtectedQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//             ProtectedQueueInfo.queueFamilyIndex = FamilyIndices.ProtectedFamily;
//             ProtectedQueueInfo.queueCount = ProtectedCount;
//             std::cout << "Protected Queue Info Pushed" << std::endl;
//             QueueInfos.push_back(ProtectedQueueInfo);
//         }

//         if(OpticFlowCount > 0)
//         {
//             VkDeviceQueueCreateInfo OpticFlowQueueInfo{};
//             OpticFlowQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//             OpticFlowQueueInfo.queueFamilyIndex = FamilyIndices.OpticFlowFamily;
//             OpticFlowQueueInfo.queueCount = OpticFlowCount;
//             std::cout << "Optic Flow Queue Info Pushed" << std::endl;
//             QueueInfos.push_back(OpticFlowQueueInfo);
//         }

//         #ifdef VK_ENABLE_BETA_EXTENSIONS
//             if(DecodeCount > 0)
//             {
//                 VkDeviceQueueCreateInfo DecodeQueueInfo{};
//                 DecodeQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//                 DecodeQueueInfo.queueFamilyIndex = FamilyIndices.DecodeFamily;
//                 DecodeQueueInfo.queueCount = DecodeCount;
//                 std::cout << "Decode Queue Info Pushed" << std::endl;
//                 QueueInfos.push_back(DecodeQueueInfo);
//             }

//             if(EncodeCount > 0)
//             {
//                 VkDeviceQueueCreateInfo EncodeQueueInfo{};
//                 EncodeQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//                 EncodeQueueInfo.queueFamilyIndex = FamilyIndices.EncodeFamily;
//                 EncodeQueueInfo.queueCount = EncodeCount;
//                 std::cout << "Encode Queue Info Pushed" << std::endl;   
//                 QueueInfos.push_back(EncodeQueueInfo);
//             }
//         #endif

//         VkPhysicalDeviceFeatures DeviceFeatures;
//         vkGetPhysicalDeviceFeatures(PDevice->VkPhysDev, &DeviceFeatures);

//         VkDeviceCreateInfo DevInfo{};
//         DevInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        
//         DevInfo.queueCreateInfoCount = QueueInfos.size();
//         DevInfo.pQueueCreateInfos = QueueInfos.data();

//         DevInfo.pEnabledFeatures = &DeviceFeatures;

//         DevInfo.enabledExtensionCount = DeviceExtensions.size();
//         DevInfo.ppEnabledExtensionNames = DeviceExtensions.data();

//         if(vkCreateDevice(PDevice->VkPhysDev, &DevInfo, nullptr, &VkDev) != VK_SUCCESS)
//         {
//             ThrowError("Failed to create Device");
//         }

//         GraphicsQueues.resize(GraphicsCount);
//         ComputeQueues.resize(ComputeCount);
//         TransferQueues.resize(TransferCount);
//         SparseBindingQueues.resize(SparseBindCount);
//         ProtectedQueues.resize(ProtectedCount);
//         OpticFlowQueues.resize(OpticFlowCount);
//         #ifdef VK_ENABLE_BETA_EXTENSIONS
//             DecodeQueues.resize(DecodeCount);
//             EncodeQueues.resize(EncodeCount);
//         #endif

//         for(int i = 0; i < GraphicsCount; i++)
//         {
//             vkGetDeviceQueue(VkDev, FamilyIndices.GraphicsFamily, i, &(GraphicsQueues[i].VulkanQueue));
//         }

//         for(int i = 0; i < ComputeCount; i++)
//         {
//             vkGetDeviceQueue(VkDev, FamilyIndices.ComputeFamily, i, &ComputeQueues[i].VulkanQueue);
//         }

//         for(int i = 0; i < TransferCount; i++)
//         {
//             vkGetDeviceQueue(VkDev, FamilyIndices.TransferFamily, i, &TransferQueues[i].VulkanQueue);
//         }
        
//         for(int i = 0; i < SparseBindCount; i++)
//         {
//             vkGetDeviceQueue(VkDev, FamilyIndices.SparseBindingFamily, i, &SparseBindingQueues[i].VulkanQueue);
//         }

//         for(int i = 0; i < ProtectedCount; i++)
//         {
//             vkGetDeviceQueue(VkDev, FamilyIndices.ProtectedFamily, i, &ProtectedQueues[i].VulkanQueue);
//         }

//         for(int i = 0; i < OpticFlowCount; i++)
//         {
//             vkGetDeviceQueue(VkDev, FamilyIndices.OpticFlowFamily, i, &ProtectedQueues[i].VulkanQueue);
//         }
        
//         #ifdef VK_ENABLE_BETA_EXTENSIONS
//             for(int i = 0; i < DecodeCount; i++)
//             {
//                 vkGetDeviceQueue(VkDev, FamilyIndices.DecodeFamily, i, &DecodeQueues[i].VulkanQueue);
//             }

//             for(int i = 0; i < EncodeCount; i++)
//             {
//                 vkGetDeviceQueue(VkDev, FamilyIndices.EncodeCount, i, &EncodeQueues[i].VulkanQueue);
//             }
//         #endif

//         InitVMA();

//         VkDevice* DevHandle = &VkDev;
//         DelQueue([DevHandle](){ vkDestroyDevice(*DevHandle, nullptr); });
//     }

//     // Queue Type is a string indicating what type of queue you are using, Options are graphics, compute, transfer, "sparse bind", protected, "optic flow", decode, and encode
//     Ek::CmdPool* Device::CreateCommandPool(QueueType QType)
//     {
//         if(QType & QueueType::Graphics)
//         {
//             Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.GraphicsFamily, &DelQueue);
//             DelQueue([Pool](){ delete Pool; });
//             return Pool;
//         }
//         else if(QType & QueueType::Compute)
//         {
//             Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.ComputeFamily, &DelQueue);
//             DelQueue([Pool](){ delete Pool; });
//             return Pool;
//         }
//         else if(QType & QueueType::Transfer)
//         {
//             Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.TransferFamily, &DelQueue);
//             DelQueue([Pool](){ delete Pool; });
//             return Pool;
//         }
//         else if(QType & QueueType::SparseBind)
//         {
//             Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.SparseBindingFamily, &DelQueue);
//             DelQueue([Pool](){ delete Pool; });
//             return Pool;
//         }
//         else if(QType & QueueType::Protected)
//         {
//             Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.ProtectedFamily, &DelQueue);
//             DelQueue([Pool](){ delete Pool; });
//             return Pool;
//         }
//         else if(QType & QueueType::OpticFlow)
//         {
//             Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.OpticFlowFamily, &DelQueue);
//             DelQueue([Pool](){ delete Pool; });
//             return Pool;
//         }
//         #ifdef VK_ENABLE_BETA_EXTENSIONS
//             else(QType & QueueType::Decode)
//             {
//                 Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.DecodeFamily, &DelQueue);
//                 DelQueue([Pool](){ delete Pool; });
//                 return Pool;
//             }
//             else(QType & QueueType::Encode)
//             {
//                 Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.EncodeFamily, &DelQueue);
//                 DelQueue([Pool](){ delete Pool; });
//                 return &Pool;
//             }
//         #endif
//         ThrowError("Failed to create CommandPool");
//     }

// }
