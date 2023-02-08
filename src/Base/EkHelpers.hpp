#pragma once

#include <Rendering/EkPipeline.hpp>
#include <Base/EkWindow.hpp>

static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData)
{
    if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
    {
        std::cout << "validation layer: " << pCallbackData->pMessage << std::endl;
    }
    return VK_FALSE;
}

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
    public:
// Instance:
        void CreateInstance();
    // Instance Ext/Layers
        bool CheckInstanceExtensionSupport(const char* ExtensionName, const char* ExtensionLayer = NULL);
        bool CheckLayerSupport(const char* LayerName);
        void RequestInstanceExtension(const char* ExtensionName);
        void RequestLayer(const char* LayerName);

// Physical Device:
        void PickPhysDev();
        bool CheckDevice(VkPhysicalDevice* PhysicalDevice);

// Device:
        void CreateDevice(std::vector<std::string>* DesiredQueues);
    // Ext
        void RequestDeviceExtension(const char* ExtensionName);
        bool CheckDeviceExtensionSupport(const char* ExtensionName);

    // Device CreationHelpers
        void FindQueueFamilies();

        void ListQueueFamilies();

    #ifdef GLFWAPP
        Ek::Window* Window;
    #endif

    //Queues
        QueueFamilyIndices FamilyIndices;
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

    private:


        int Width = 1280;
        int Height = 720;

        std::vector<const char*> Layers;
        std::vector<const char*> Extensions;
        std::vector<const char*> DeviceExtensions;

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

    // Initiation

        void InitVMA();

    #ifdef GLFWAPP
        Ek::Window* CreateWindow(int Width, int Height, const char* AppName);
    #endif
};
