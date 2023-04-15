#pragma once

#include <Base/EkWindow.hpp>
#include <Base/PhysicalDevice.h>
#include <Rendering/EkPipeline.hpp>

#include <stb/stb_image.h>

enum QueueType
{
    Graphics =   0x00000001,
    Compute =    0x00000010,
    Transfer =   0x00000100,
    SparseBind = 0x00001000,
    Protected =  0x00010000,
    OpticFlow =  0x00100000,
    #ifdef VK_ENABLE_BETA_EXTENSIONS
        Decode = 0x01000000,
        Encode = 0x10000000
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

    class Device
    {
    public:
        Device()
        {}
        Device(VkPhysicalDevice* PhysDev) : PDev{PhysDev}
        {}

        VkDevice VkDev;
        void RequestExtension(const char* ExtensionName);


        void Create(Instance* Inst, QueueList* DesiredQueues, Ek::Queues* Queues);

        AllocatedImage CreateTexture(VkImageType ImageType, VkExtent3D Extent, VkFormat ImageFormat, VkImageLayout Layout, VmaMemoryUsage MemUse, uint32_t MipLevels, VkImageUsageFlags ImageUsage, void* pNext = nullptr);
        AllocatedImage LoadTexture(const char* Path);
   
        Shader CreateShader(const char* FileName);

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
