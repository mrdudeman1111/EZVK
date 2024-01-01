#include <Base/EkTypes.hpp>

namespace Ek
{
    class Instance
    {
        public:
        ~Instance();

        VkInstance VkInst;

        void CreateInstance(uint32_t VkVersion, const char* AppName);

        void RequestInstanceExtension(const char* ExtensionName);
        void RequestLayer(const char* LayerName);

        private:
        DeleteQueue DelQueue;
        bool CheckInstanceExtensionSupport(const char* ExtensionName, const char* ExtensionLayer = NULL);
        bool CheckLayerSupport(const char* LayerName);

        std::vector<const char*> Layers;
        std::vector<const char*> Extensions;
    };
}
