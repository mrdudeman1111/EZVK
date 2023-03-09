#include <Base/Device.h>

namespace Ek
{
    bool PhysicalDevice::CheckDevice(VkPhysicalDevice* PhysicalDevice)
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

    Device PhysicalDevice::GetDevice()
    {
        return *new Device(&VkPhysDev);
    }

    void PhysicalDevice::PickPhysDev(Instance* Instance)
    {
        uint32_t DeviceCount = 0;
        vkEnumeratePhysicalDevices(Instance->VkInst, &DeviceCount, nullptr);

        std::vector<VkPhysicalDevice> Devices(DeviceCount);
        vkEnumeratePhysicalDevices(Instance->VkInst, &DeviceCount, Devices.data());

        std::cout << "You have " << Devices.size() << " Physical Devices\n";

        if(DeviceCount == 0)
        {
            ThrowError("Failed to find Physical Device with vulkan support");
        }
        
        for(uint32_t i = 0; i < Devices.size(); i++) 
        {
            if(CheckDevice(&Devices[i])) 
            {
                VkPhysDev = Devices[i];
                return;
            }
        }

        throw std::runtime_error("Failed to find supported PhysDev");
    }
}
