#include <Base/Instance.h>

namespace Ek
{
    class PhysicalDevice
    {
        public:
        VkPhysicalDevice VkPhysDev;
        // Physical Device:
            void PickPhysDev(Instance* Instance);
            struct Device GetDevice();

        private:
            bool CheckDevice(VkPhysicalDevice* PhysicalDevice);
    };
}
