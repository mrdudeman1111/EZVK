#include <cstdint>
#include <map>
#include <Base/Instance.h>
#include <vulkan/vulkan_core.h>

namespace Ek
{
    class PhysicalDevice
    {
        public:
            VkPhysicalDevice VkPhysDev;
        // Physical Device:
            void PickPhysDev(Instance* Instance);
            struct Device GetLogicalDevice();
            uint32_t GetMemType(VkMemoryPropertyFlags Props);

        private:
            bool CheckDevice(VkPhysicalDevice* PhysicalDevice);
    };
}
