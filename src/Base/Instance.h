#include <Base/EkTypes.hpp>

namespace Ek
{
    class Instance
    {
        public:
        VkInstance VkInst;

        void CreateInstance();

        void RequestInstanceExtension(const char* ExtensionName);
        void RequestLayer(const char* LayerName);

        private:
        bool CheckInstanceExtensionSupport(const char* ExtensionName, const char* ExtensionLayer = NULL);
        bool CheckLayerSupport(const char* LayerName);

        std::vector<const char*> Layers;
        std::vector<const char*> Extensions;
    };
}
