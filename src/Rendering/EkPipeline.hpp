#pragma once

#include <Base/EkTypes.hpp>


namespace Ek
{
    // Add Push Constant support
    struct Shader
    {
        public:
        VkShaderModule ShaderModule;

        void AddShaderInput(VkDevice* pDev, uint32_t Location, VkDescriptorType Type, uint32_t InputCount = 1);
        void BuildShaderLayout();

        std::vector<VkDescriptorSetLayout> DescriptorLayouts;
        std::vector<VkDescriptorSet> DescriptorSets;

        // Shader Name is the name of the entrypoint function in the shader (the example shader entrypoint functions are main so This name will be name)
        const char* ShaderEntryPoint;
        VkShaderStageFlagBits Stage;

        private:
        VkDevice* p_Dev;
        std::vector<VkDescriptorPoolSize> PoolSizes;
        VkDescriptorPool DescriptorPool;

        std::vector<VkDescriptorSetLayoutBinding> DescriptorBindings;

        uint32_t LayoutIterator = 0;
    };

    class PipeLayout
    {
        public:
        std::vector<VkDescriptorSetLayout> Descriptors;
        std::vector<VkPushConstantRange> PushConstants;
    };

    class Pipeline
    {
        public:
        Pipeline();

        Pipeline(VkDevice* Dev, VkRenderPass* Rp, uint32_t Height, uint32_t Width) : p_Renderpass{Rp}, Height{Height}, Width{Width}
        {
            p_Dev = Dev;
        }

        ~Pipeline()
        {
            CleanupQueue.Run();
        }

        std::vector<Shader*> Shaders;

        uint32_t Height, Width;

        VertexType VT;

        PipeLayout PipelineLayout;

        void Build(uint32_t SubpassToUse);

        private:
        VkDevice* p_Dev;

        VkRenderPass* p_Renderpass;
        VkPipeline VkPipe;
        VkPipelineLayout VkPipeLayout;


        DeleteQueue CleanupQueue;
        VkViewport ViewPort;
    };

    class ShaderInput
    {
        public:
        VkDescriptorPool DescriptorPool;
        std::vector<VkDescriptorSet> Descriptors;

        void CreateDescriptorPool(VkDevice* Dev, Pipeline* Pipe, VkDescriptorType Type);
    };

}
