#pragma once

#include <Base/EkWindow.hpp>
#include <Base/PhysicalDevice.h>
#include <Rendering/EkPipeline.hpp>

enum QueueType
{
    Graphics = 1,
    Compute = 2,
    Transfer = 4,
    SparseBind = 8,
    Protected = 16,
    OpticFlow = 32
    #ifdef VK_ENABLE_BETA_EXTENSIONS
        ,
        Decode = 64,
        Encode = 128
    #endif
};

struct QueueFamilyIndices
{
    uint32_t GraphicsFamily = -1;
    uint32_t GraphicsCount = -1;
    uint32_t GraphicsFlags = 0;

    uint32_t ComputeFamily = -1;
    uint32_t ComputeCount = -1;
    uint32_t ComputeFlags = 0;

    uint32_t TransferFamily = -1;
    uint32_t TransferCount = -1;
    uint32_t TransferFlags = 0;

    uint32_t SparseBindingFamily = -1;
    uint32_t SparseBindingCount = -1;
    uint32_t SparseBindingFlags = 0;

    uint32_t ProtectedFamily = -1;
    uint32_t ProtectedCount = -1;
    uint32_t ProtectedFlags = 0;

    uint32_t OpticFlowFamily = -1;
    uint32_t OpticFlowCount = -1;
    uint32_t OpticFlowFlags = 0;

    #ifdef VK_ENABLE_BETA_EXTENSIONS
        // Provided by VK_KHR_video_decode_queue
        uint32_t DecodeFamily = -1;
        uint32_t DecodeCount = -1;
        uint32_t DecodeFlags = 0;
        // Provided by VK_KHR_video_encode_queue
        uint32_t EncodeFamily = -1;
        uint32_t EncodeCount = -1;
        uint32_t EncodeFlags = 0;
    #endif
};


typedef std::map<QueueType, int> QueueList;

namespace Ek
{
    struct Queue
    {
        VkQueue VulkanQueue;
        bool Used;
    };

    class Queues
    {
        public:
        std::vector<Queue> GraphicsQueues;
        std::vector<Queue> ComputeQueues;
        std::vector<Queue> TransferQueues;
        std::vector<Queue> SparseBindingQueues;
        std::vector<Queue> ProtectedQueues;
        std::vector<Queue> OpticFlowQueues;
        #ifdef VK_ENABLE_BETA_EXTENSIONS
            std::vector<Queue> DecodeQueues;
            std::vector<Queue> EncodeQueues;
        #endif
    };

    struct EkShader
    {
        VkShaderModule ShaderModule;
        
        // Shader Name is the name of the entrypoint function in the shader (the example shader entrypoint functions are main so This name will be name)
        const char* ShaderEntryPointName;
        VkShaderStageFlagBits Stage;
    };

    class Device
    {
    public:
        Device()
        {}
        Device(VkPhysicalDevice* PhysDev) : PDev{PhysDev}
        {}

        VkDevice VkDev;
        void RequestExtension(const char* ExtensionName);


        void Create(Instance* Inst, PhysicalDevice* PDevice, QueueList DesiredQueues, Ek::Queues* Queues);

        AllocatedImage CreateTexture(VkImageType ImageType, VkExtent3D Extent, VkFormat ImageFormat, VkImageLayout Layout, VmaMemoryUsage MemUse, uint32_t MipLevels, VkImageUsageFlags ImageUsage);
        AllocatedImage LoadTexture(const char* Path, VkExtent3D* Extent);
   
        EkShader CreateShader(std::string& FileName);

        Window* CreateWindow(Ek::Queue* PresentQueue);

        Ek::CmdPool* CreateCommandPool(QueueType QueueType);

        Ek::Renderpass CreateRenderpass();

    private:
        VkPhysicalDevice* PDev;
        VkInstance* PInstance;
        VmaAllocator Allocator;

        void ListQueueFamilies();
        void FindQueueFamilies();
        bool CheckDeviceExtensionSupport(const char* ExtensionName);
        void InitVMA();

        std::vector<const char*> DeviceExtensions;

        //Queues
        QueueFamilyIndices FamilyIndices;
    };
}
