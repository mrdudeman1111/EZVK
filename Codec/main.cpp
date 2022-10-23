#include <iostream>
#include <stack>
#include <functional>
#define VK_ENABLE_BETA_EXTENSIONS
#include <vulkan/vulkan.hpp>

const std::vector<const char*> Extensions = {};
const std::vector<const char*> DevExt = {"VK_KHR_video_queue", "VK_KHR_video_encode_queue", "VK_KHR_video_decode_queue", "VK_EXT_video_encode_h265", "VK_EXT_video_decode_h265"};
const std::vector<const char*> Layers = {"VK_LAYER_KHRONOS_validation"};


struct VulkanBaseStructs
{
    public:
    vk::Instance Instance;
    vk::PhysicalDevice PhysDev;
    vk::Device Device;
    vk::Queue GraphicsQueue;
    vk::Queue ComputeQueue;
    vk::Queue EncodeQueue;
    uint32_t GraphicsFamily, ComputeFamily, EncodeFamily;

    void Build()
    {
        vk::InstanceCreateInfo InstCI{};
        InstCI.enabledExtensionCount = Extensions.size();
        InstCI.enabledLayerCount = Layers.size();
        InstCI.ppEnabledExtensionNames = Extensions.data();
        InstCI.ppEnabledLayerNames = Layers.data();

        Instance = vk::createInstance(InstCI);

        std::vector<vk::PhysicalDevice> PhysDevs = Instance.enumeratePhysicalDevices();

        for(const vk::PhysicalDevice PhysicalDev : PhysDevs)
        {
            vk::PhysicalDeviceProperties DevProperties = PhysicalDev.getProperties();
            if(DevProperties.apiVersion == 1.2 && DevProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
            {
                PhysDev = PhysicalDev;
            }
        }

        std::vector<vk::QueueFamilyProperties> QueueFamilyProperties = PhysDev.getQueueFamilyProperties();

        uint32_t GraphicsQueueCount, ComputeQueueCount, EncodeQueueCount;

        for(uint i = 0; i < QueueFamilyProperties.size(); i++)
        {
            if(QueueFamilyProperties[i].queueFlags == vk::QueueFlagBits::eGraphics)
            {
                GraphicsQueueCount = QueueFamilyProperties[i].queueCount;
                GraphicsFamily = i;
            }
            
            if(QueueFamilyProperties[i].queueFlags == vk::QueueFlagBits::eCompute)
            {
                ComputeQueueCount = QueueFamilyProperties[i].queueCount;
                ComputeFamily = i;
            }
            
            if(QueueFamilyProperties[i].queueFlags == vk::QueueFlagBits::eVideoEncodeKHR)
            {
                EncodeQueueCount = QueueFamilyProperties[i].queueCount;
                EncodeFamily = i;
            }
        }

        vk::DeviceQueueCreateInfo GraphicsQueueCI{};
        GraphicsQueueCI.queueCount = GraphicsQueueCount;
        GraphicsQueueCI.queueFamilyIndex = GraphicsFamily;

        vk::DeviceQueueCreateInfo ComputeQueueCI{};
        ComputeQueueCI.queueCount = ComputeQueueCount;
        ComputeQueueCI.queueFamilyIndex = ComputeFamily;
        
        vk::DeviceQueueCreateInfo EncodeQueueCI{};
        EncodeQueueCI.queueCount = EncodeQueueCount;
        EncodeQueueCI.queueFamilyIndex = EncodeFamily;

        vk::DeviceQueueCreateInfo QueueCIs[3] = { GraphicsQueueCI, ComputeQueueCI, EncodeQueueCI };

        vk::DeviceCreateInfo DevCI{};
        DevCI.queueCreateInfoCount = 3;
        DevCI.pQueueCreateInfos = QueueCIs;
        DevCI.enabledExtensionCount = DevExt.size();
        DevCI.ppEnabledExtensionNames = DevExt.data();

        Device = PhysDev.createDevice( DevCI );

        GraphicsQueue = Device.getQueue(GraphicsFamily, 0);
        ComputeQueue = Device.getQueue(ComputeFamily, 0);
    }

    void Delete()
    {
        Device.destroy(nullptr);
        Instance.destroy(nullptr);
    }
};

struct VideoEncoder
{
    public:
    void build()
    {

    }
};

int main()
{
    VulkanBaseStructs VkStructs;
    VkStructs.Build();
    VkStructs.Delete();

    std::string ExitConfirm;
    std::cin >> ExitConfirm;

    return 0;
}
