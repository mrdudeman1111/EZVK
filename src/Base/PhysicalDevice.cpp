#include <Base/Device.h>
#include <vulkan/vulkan_core.h>

namespace Ek
{
    bool PhysicalDevice::CheckDevice(VkPhysicalDevice* PhysicalDevice)
    {
        VkPhysicalDeviceProperties DeviceProperties;
        vkGetPhysicalDeviceProperties(*PhysicalDevice, &DeviceProperties);

        VkPhysicalDeviceFeatures DeviceFeatures;
        vkGetPhysicalDeviceFeatures(*PhysicalDevice, &DeviceFeatures);

        std::cout << DeviceProperties.deviceName << std::endl;

        if(DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
        {
            return true;
        }
        return false;
    }

    Device PhysicalDevice::GetLogicalDevice()
    {
        return *new Device(&VkPhysDev);
    }

    void PhysicalDevice::PickPhysDev(Instance* Instance)
    {
        uint32_t DeviceCount = 0;
        vkEnumeratePhysicalDevices(Instance->VkInst, &DeviceCount, nullptr);

        std::vector<VkPhysicalDevice> Devices(DeviceCount);
        vkEnumeratePhysicalDevices(Instance->VkInst, &DeviceCount, Devices.data());

        if(DeviceCount == 0)
        {
            ThrowError("Failed to find Physical Device with vulkan support");
        }

        std::cout << "Found " << Devices.size() << " Physical Devices:\n";

        for(uint32_t i = 0; i < Devices.size(); i++) 
        {
            if(CheckDevice(&Devices[i])) 
            {
                VkPhysDev = Devices[i];
                break;
            }
        }
    }

    uint32_t PhysicalDevice::GetMemType(VkMemoryPropertyFlags Props)
    {
      VkPhysicalDeviceMemoryProperties memProperties;
      vkGetPhysicalDeviceMemoryProperties(VkPhysDev, &memProperties);

      for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
      {
        if(memProperties.memoryTypes[i].propertyFlags & Props)
        {
            return i;
        }
      }

      return -1;
    }
}
