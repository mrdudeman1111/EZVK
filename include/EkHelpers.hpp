#pragma once

#include <EkTypes.hpp>

namespace Mesh
{
    // glm::mat4 ConvertMat4(aiMatrix4x4 AssimpMatrix);
}

struct EkQueue
{
    VkQueue VulkanQueue;
    bool Used;
};

struct QueueFamilyIndices
{
    uint32_t GraphicsFamily = 99;
    uint32_t ComputeFamily = 99;
    uint32_t TransferFamily = 99;
    uint32_t SparseBindingFamily = 99;
    uint32_t ProtectedFamily = 99;
    uint32_t OpticFlowFamily = 99;

    #ifdef VK_ENABLE_BETA_EXTENSIONS
        // Provided by VK_KHR_video_decode_queue
        uint32_t DecodeFamily;
        // Provided by VK_KHR_video_encode_queue
        uint32_t EncodeFamily;
    #endif
};

class EkVulkan
{
    private:
    // Basic Structures
        VkDebugUtilsMessengerEXT DebugMessenger;
        VkPhysicalDevice PhysDev;
        VkInstance Instance;
        
        // Device
            VkDevice Device;
            std::vector<EkQueue> GraphicsQueues;
            std::vector<EkQueue> ComputeQueues;
            std::vector<EkQueue> TransferQueues;
            std::vector<EkQueue> SparseBindingQueues;
            std::vector<EkQueue> ProtectedQueues;
            std::vector<EkQueue> OpticFlowQueues;
            #ifdef VK_ENABLE_BETA_EXTENSIONS
                std::vector<EkQueue> DecodeQueues;
                std::vector<EkQueue> EncodeQueues;
            #endif

        QueueFamilyIndices FamilyIndices;

        VmaAllocator Allocator;

        VkSwapchainKHR Swapchain;

    public:
    #ifdef GLFWAPP
        EkWindow Window;
    #endif
    // My Custom Structures
        DeleteQueue DeletionQueue;
    private:


    // Constants
        int Width = 1280;
        int Height = 720;

        std::vector<const char*> Layers;
        std::vector<const char*> Extensions;

    // Layouts
        VkDescriptorSetLayout CameraLayout;
        VkDescriptorSetLayout SkeletalLayout;

    public:

    EkVulkan()
    {

    }

    // Create Helpers
        EkCmdPool* CreateCommandPool(std::string QueueType);

    // Query/Request

        void CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, AllocatedBuffer* AllocatedBuffer, VmaMemoryUsage MemUse);

        // Deprecated
        bool CheckDeviceExtensionSupport(const char* ExtensionName, const char* ExtensionLayer = NULL);

        bool CheckDevice(VkPhysicalDevice* PhysicalDevice);

        // Instance Ext/Layers
            bool CheckInstanceExtensionSupport(const char* ExtensionName, const char* ExtensionLayer = NULL);
            bool CheckLayerSupport(const char* LayerName);
            void RequestLayer(const char* LayerName);
            void PrintAvailableLayers();
            void RequestInstanceExtension(const char* ExtensionName);


        void FindQueueFamilies();

        void ListQueueFamilies();

    // Initiation

        static void DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);

        
        void InitVMA();

        void CreateWindow(int Width, int Height, const char* AppName);

        void CreateInstance();

        void PickPhysDev();

        void CreateDevice(std::vector<std::string>* DesiredQueues);

        void CreateSwapChain(VkFormat ImageFormat);
};

namespace Pipeline
{
    // VkShaderModule CreateShaderModule(std::string& FileName);

    // VkWriteDescriptorSet WriteToDescriptor(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorBufferInfo* bufferInfo , uint32_t binding);

    // // When messing with descriptors you do have to mess with the pipelinelayout in CreateGraphicsPipeline
    // void CreateGraphicsPipeline();
}
