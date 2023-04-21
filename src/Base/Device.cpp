#include <vulkan/vulkan_core.h>
#define STB_IMAGE_IMPLEMENTATION
#include <Base/Device.h>
#include <cstring>

namespace Ek
{
    // Idea: custom enum to show image type for layout info, Image Type info, and memoryusage.
    AllocatedImage Device::CreateTexture(VkImageType ImageType, VkExtent3D Extent, VkFormat ImageFormat, VkImageLayout Layout, VmaMemoryUsage MemUse, uint32_t MipLevels, VkImageUsageFlags ImageUsage, void* pNext)
    {
        AllocatedImage Image(&VkDev);

        Image.Format = ImageFormat;
        Image.Layout = Layout;

        VkImageCreateInfo ImageCI = {};
        ImageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ImageCI.imageType = ImageType;
        ImageCI.format = ImageFormat;
        ImageCI.extent = Extent;
        ImageCI.mipLevels = MipLevels;
        ImageCI.arrayLayers = 1;
        ImageCI.samples = VK_SAMPLE_COUNT_1_BIT;
        ImageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
        ImageCI.usage = ImageUsage;

        if(pNext)
        {
            ImageCI.pNext = pNext;
        }

        if(vkCreateImage(VkDev, &ImageCI, nullptr, &Image.Image) != VK_SUCCESS)
        {
          throw std::runtime_error("Failed to Create Image");
        }

        VmaAllocationCreateInfo AllocInfo = {};
        AllocInfo.usage = MemUse;

        vmaCreateImage(Allocator, &ImageCI, &AllocInfo, &Image.Image, &Image.Allocation, nullptr);

        return Image;
    }

    AllocatedImage Device::LoadTexture(const char* Path)
    {
        int Height, Width, Channels;
        stbi_uc* Pixels = stbi_load(Path, &Width, &Height, &Channels, STBI_rgb_alpha);

        VkExtent3D Extent;
        Extent.width = Width;
        Extent.height = Height;
        Extent.depth = 1.0f;

        AllocatedImage Texture = CreateTexture(VK_IMAGE_TYPE_3D, Extent, VK_FORMAT_R32G32B32_UINT, VK_IMAGE_LAYOUT_GENERAL, VmaMemoryUsage::VMA_MEMORY_USAGE_CPU_TO_GPU, 1, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);

        void* DstMem;

        vmaMapMemory(Allocator, Texture.Allocation, &DstMem);
            memcpy(DstMem, Pixels, Width * Height * 4);
        vmaUnmapMemory(Allocator, Texture.Allocation);

        stbi_image_free(Pixels);

        return Texture;
    }

    bool Device::CheckDeviceExtensionSupport(const char* ExtensionName)
    {
        uint32_t ExtCount = 0;

        vkEnumerateDeviceExtensionProperties(*PDev, nullptr, &ExtCount, nullptr);

        std::vector<VkExtensionProperties> DeviceExtensions(ExtCount);
        
        if(vkEnumerateDeviceExtensionProperties(*PDev, nullptr, &ExtCount, DeviceExtensions.data()) != VK_SUCCESS)
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

    void Device::RequestExtension(const char* ExtensionName)
    {
        if(CheckDeviceExtensionSupport(ExtensionName))
        {
            DeviceExtensions.push_back(ExtensionName);
            std::cout << "Device extension " << ExtensionName << " is available\n";
        }
        else
        {
            std::cout << "Device extension " << ExtensionName << " is not available\n";
        }
    }

    void Device::ListQueueFamilies()
    {
        uint32_t QueueFamilyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(*PDev, &QueueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(*PDev, &QueueFamilyCount, QueueFamilies.data());

        for(uint32_t i = 0; i < QueueFamilies.size(); i++)
        {
            std::cout << "Queue at " << i << " Has ";
            std::cout << QueueFamilies[i].queueCount << " Queues and is a ";
            std::cout << QueueFamilies[i].queueFlags << " queue" << std::endl;
        }
    }

    void Device::FindQueueFamilies()
    {
        uint32_t QueueFamCount;
        vkGetPhysicalDeviceQueueFamilyProperties(*PDev, &QueueFamCount, nullptr);

        std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamCount);
        vkGetPhysicalDeviceQueueFamilyProperties(*PDev, &QueueFamCount, QueueFamilies.data());

        for(uint32_t i = 0; i < QueueFamilies.size(); i++)
        {
            if(QueueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            {
                FamilyIndices.GraphicsFamily = i;
                FamilyIndices.GraphicsCount = QueueFamilies[i].queueCount;
                FamilyIndices.GraphicsFlags = QueueFamilies[i].queueFlags;
            }

            else if(QueueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT)
            {
                FamilyIndices.ComputeFamily = i;
                FamilyIndices.ComputeCount = QueueFamilies[i].queueCount;
                FamilyIndices.ComputeFlags = QueueFamilies[i].queueFlags;
            }
            
            else if(QueueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT)
            {
                FamilyIndices.TransferFamily = i;
                FamilyIndices.TransferCount = QueueFamilies[i].queueCount;
                FamilyIndices.TransferFlags = QueueFamilies[i].queueFlags;
            }

            else if(QueueFamilies[i].queueFlags & VK_QUEUE_PROTECTED_BIT)
            {
                FamilyIndices.ProtectedFamily = i;
                FamilyIndices.ProtectedCount = QueueFamilies[i].queueCount;
                FamilyIndices.ProtectedFlags = QueueFamilies[i].queueFlags;
            }
            
            #ifdef VK_ENABLE_BETA_EXTENSIONS
                else if(QueueFamilies[i].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR)
                {
                    FamilyIndices.DecodeFamily = i;
                    FamilyIndices.DecodeCount = QueueFamilies[i].queueCount;
                    FamilyIndices.DecodeFlags = QueueFamilies[i].queueFlags;
                }

                else if(QueueFamilies[i].queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR)
                {
                    FamilyIndices.EncodeFamily = i;
                    FamilyIndices.EncodeCount = QueueFamilies[i].queueCount;
                    FamilyIndices.EncodeFlags = QueueFamilies[i].queueFlags;
                }
            #endif

            else
            {
                std::cout << "Failed to parse queue" << std::endl;
            }
        }
    }


    void Device::InitVMA()
    {
        VmaAllocatorCreateInfo AllocatorInfo = {};
        AllocatorInfo.instance = *PInstance;
        AllocatorInfo.physicalDevice = *PDev;
        AllocatorInfo.device = VkDev;
        vmaCreateAllocator(&AllocatorInfo, &Allocator);
    }

    void Device::Create(Instance* Inst, QueueList* DesiredQueues, Ek::Queues* Queues)
    {
        PInstance = &Inst->VkInst;

        // Fills FamilyIndices member, which contains the index for every queue family
        FindQueueFamilies();
        std::cout << "Family indices full" << std::endl;

        std::vector<VkDeviceQueueCreateInfo> QueueInfos;
        int GraphicsCount, ComputeCount, TransferCount, SparseBindCount, ProtectedCount, OpticFlowCount;
        #ifdef VK_ENABLE_BETA_EXTENSIONS
            int DecodeCount, EncodeCount;
        #endif

        if(DesiredQueues)
        {
            GraphicsCount = (DesiredQueues->at(QueueType::Graphics) > FamilyIndices.GraphicsCount) ? FamilyIndices.GraphicsCount : DesiredQueues->at(QueueType::Graphics);
            ComputeCount = (DesiredQueues->at(QueueType::Compute) > FamilyIndices.ComputeCount) ? FamilyIndices.ComputeCount : DesiredQueues->at(QueueType::Compute);
            TransferCount = (DesiredQueues->at(QueueType::Transfer) > FamilyIndices.TransferCount) ? FamilyIndices.TransferCount : DesiredQueues->at(QueueType::Transfer);
            SparseBindCount = (DesiredQueues->at(QueueType::SparseBind) > FamilyIndices.SparseBindingCount) ? FamilyIndices.SparseBindingCount : DesiredQueues->at(QueueType::SparseBind);
            ProtectedCount = (DesiredQueues->at(QueueType::Protected) > FamilyIndices.ProtectedCount) ? FamilyIndices.ProtectedCount : DesiredQueues->at(QueueType::SparseBind);
            OpticFlowCount = (DesiredQueues->at(QueueType::OpticFlow) > FamilyIndices.OpticFlowCount) ? FamilyIndices.OpticFlowCount : DesiredQueues->at(QueueType::OpticFlow);

            #ifdef VK_ENABLE_BETA_EXTENSIONS
                DecodeCount = (DesiredQueues[QueueType::Decode] > FamilyIndices.DecodeCount) ? FamilyIndices.DecodeCount : DesiredQueues[QueueType::Decode];
                EncodeCount = (DesiredQueues[QueueType::Encode] > FamilyIndices.EncodeCount) ? FamilyIndices.EncodeCount : DesiredQueues[QueueType::Encode];
            #endif

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
        }

        VkPhysicalDeviceFeatures DeviceFeatures;
        vkGetPhysicalDeviceFeatures(*PDev, &DeviceFeatures);

        VkDeviceCreateInfo DevInfo{};
        DevInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        
        DevInfo.queueCreateInfoCount = QueueInfos.size();
        DevInfo.pQueueCreateInfos = QueueInfos.data();

        DevInfo.pEnabledFeatures = &DeviceFeatures;

        DevInfo.enabledExtensionCount = DeviceExtensions.size();
        DevInfo.ppEnabledExtensionNames = DeviceExtensions.data();

        if(vkCreateDevice(*PDev, &DevInfo, nullptr, &VkDev) != VK_SUCCESS)
        {
            ThrowError("Failed to create Device");
        }

        if(DesiredQueues)
        {
            Queues->GraphicsQueues.resize(GraphicsCount);
            Queues->ComputeQueues.resize(ComputeCount);
            Queues->TransferQueues.resize(TransferCount);
            Queues->SparseBindingQueues.resize(SparseBindCount);
            Queues->ProtectedQueues.resize(ProtectedCount);
            Queues->OpticFlowQueues.resize(OpticFlowCount);
            #ifdef VK_ENABLE_BETA_EXTENSIONS
                Queues->DecodeQueues.resize(DecodeCount);
                Queues->EncodeQueues.resize(EncodeCount);
            #endif

            for(int i = 0; i < GraphicsCount; i++)
            {
                vkGetDeviceQueue(VkDev, FamilyIndices.GraphicsFamily, i, &Queues->GraphicsQueues[i].VulkanQueue);
            }

            for(int i = 0; i < ComputeCount; i++)
            {
                vkGetDeviceQueue(VkDev, FamilyIndices.ComputeFamily, i, &Queues->ComputeQueues[i].VulkanQueue);
            }

            for(int i = 0; i < TransferCount; i++)
            {
                vkGetDeviceQueue(VkDev, FamilyIndices.TransferFamily, i, &Queues->TransferQueues[i].VulkanQueue);
            }
            
            for(int i = 0; i < SparseBindCount; i++)
            {
                vkGetDeviceQueue(VkDev, FamilyIndices.SparseBindingFamily, i, &Queues->SparseBindingQueues[i].VulkanQueue);
            }

            for(int i = 0; i < ProtectedCount; i++)
            {
                vkGetDeviceQueue(VkDev, FamilyIndices.ProtectedFamily, i, &Queues->ProtectedQueues[i].VulkanQueue);
            }

            for(int i = 0; i < OpticFlowCount; i++)
            {
                vkGetDeviceQueue(VkDev, FamilyIndices.OpticFlowFamily, i, &Queues->OpticFlowQueues[i].VulkanQueue);
            }
            
            #ifdef VK_ENABLE_BETA_EXTENSIONS
                for(int i = 0; i < DecodeCount; i++)
                {
                    vkGetDeviceQueue(VkDev, FamilyIndices.DecodeFamily, i, &Queues->DecodeQueues[i].VulkanQueue);
                }

                for(int i = 0; i < EncodeCount; i++)
                {
                    vkGetDeviceQueue(VkDev, FamilyIndices.EncodeCount, i, &Queues->EncodeQueues[i].VulkanQueue);
                }
            #endif
        }

        InitVMA();

        VkDevice* DevHandle = &VkDev;
        DelQueue([DevHandle](){ vkDestroyDevice(*DevHandle, nullptr); });
    }

    #ifdef GLFWAPP
    Window* Device::CreateWindow(Ek::Queue* PresentQueue)
    {
        Window* Win = new Ek::Window(this, PInstance, PDev, &PresentQueue->VulkanQueue);
        return Win;
    }
    #endif

    Ek::Renderpass Device::CreateRenderpass()
    {
        Ek::Renderpass Renderpass(&VkDev);
        return Renderpass;
    }

    Ek::Shader Ek::Device::CreateShader(const char* FileName)
    {
        Ek::Shader Shader;

        std::vector<char> Code = ReadFile(FileName);

        VkShaderModuleCreateInfo ShaderCI{};
        ShaderCI.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        ShaderCI.codeSize = Code.size();
        ShaderCI.pCode = reinterpret_cast<const uint32_t*>(Code.data());

        if(vkCreateShaderModule(VkDev, &ShaderCI, nullptr, &Shader.ShaderModule) != VK_SUCCESS)
        {
            ThrowError("Device: Failed to create Shader module");
        }

        return Shader;
    }

    // Queue Type is a string indicating what type of queue you are using, Options are graphics, compute, transfer, "sparse bind", protected, "optic flow", decode, and encode
    Ek::CmdPool* Device::CreateCommandPool(QueueType QType)
    {
        if(QType & QueueType::Graphics)
        {
            Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.GraphicsFamily, &DelQueue);
            DelQueue([Pool](){ delete Pool; });
            return Pool;
        }
        else if(QType & QueueType::Compute)
        {
            Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.ComputeFamily, &DelQueue);
            DelQueue([Pool](){ delete Pool; });
            return Pool;
        }
        else if(QType & QueueType::Transfer)
        {
            Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.TransferFamily, &DelQueue);
            DelQueue([Pool](){ delete Pool; });
            return Pool;
        }
        else if(QType & QueueType::SparseBind)
        {
            Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.SparseBindingFamily, &DelQueue);
            DelQueue([Pool](){ delete Pool; });
            return Pool;
        }
        else if(QType & QueueType::Protected)
        {
            Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.ProtectedFamily, &DelQueue);
            DelQueue([Pool](){ delete Pool; });
            return Pool;
        }
        else if(QType & QueueType::OpticFlow)
        {
            Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.OpticFlowFamily, &DelQueue);
            DelQueue([Pool](){ delete Pool; });
            return Pool;
        }
        #ifdef VK_ENABLE_BETA_EXTENSIONS
            else(QType & QueueType::Decode)
            {
                Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.DecodeFamily, &DelQueue);
                DelQueue([Pool](){ delete Pool; });
                return Pool;
            }
            else(QType & QueueType::Encode)
            {
                Ek::CmdPool* Pool = new Ek::CmdPool(&VkDev, FamilyIndices.EncodeFamily, &DelQueue);
                DelQueue([Pool](){ delete Pool; });
                return &Pool;
            }
        #endif
        ThrowError("Failed to create CommandPool");
        return nullptr;
    }

}
