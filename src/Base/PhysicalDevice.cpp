#include <Base/Device.h>
#include <vulkan/vulkan_core.h>
#include <vulkan/vk_enum_string_helper.h>

namespace Ek
{
    bool PhysicalDevice::CheckDevice(VkPhysicalDevice *PhysicalDevice)
    {
        VkPhysicalDeviceProperties DeviceProperties;
        vkGetPhysicalDeviceProperties(*PhysicalDevice, &DeviceProperties);

        VkPhysicalDeviceFeatures DeviceFeatures;
        vkGetPhysicalDeviceFeatures(*PhysicalDevice, &DeviceFeatures);

        std::cout << DeviceProperties.deviceName << std::endl;

        if (DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            return true;
        }
        return false;
    }

    Device PhysicalDevice::GetLogicalDevice()
    {
        return *new Device(&VkPhysDev);
    }

    void PhysicalDevice::PickPhysDev(Instance *Instance)
    {
        uint32_t DeviceCount = 0;
        vkEnumeratePhysicalDevices(Instance->VkInst, &DeviceCount, nullptr);

        std::vector<VkPhysicalDevice> Devices(DeviceCount);
        vkEnumeratePhysicalDevices(Instance->VkInst, &DeviceCount, Devices.data());

        if (DeviceCount == 0)
        {
            ThrowError("Failed to find Physical Device with vulkan support");
        }

        std::cout << "Found " << Devices.size() << " Physical Devices:\n";

        for (uint32_t i = 0; i < Devices.size(); i++)
        {
            if (CheckDevice(&Devices[i]))
            {
                VkPhysDev = Devices[i];
                break;
            }
        }
    }

    uint32_t PhysicalDevice::GetMemType(VkMemoryPropertyFlags Props)
    {
        VkPhysicalDeviceMemoryProperties MemProperties;
        vkGetPhysicalDeviceMemoryProperties(VkPhysDev, &MemProperties);

        for (uint32_t i = 0; i < MemProperties.memoryTypeCount; i++)
        {
            if (MemProperties.memoryTypes[i].propertyFlags & Props)
            {
                return i;
            }
        }

        std::cout << "Ek::PhysicalDevice::GetMemType() : couldn't find compatible memory Range\n";
        return -1;
    }
}
