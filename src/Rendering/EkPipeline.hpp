#pragma once

#include <Base/EkTypes.hpp>

namespace Shaders
{
    struct EkShader
    {
        VkShaderModule ShaderModule;
        
        // Shader Name is the name of the entrypoint function in the shader (the example shader entrypoint functions are main so This name will be name)
        const char* ShaderEntryPointName;
        VkShaderStageFlagBits Stage;
    };
    
    VkShaderModule CreateShaderModule(std::string& FileName);
}

namespace Ek
{
    class Pipeline
    {
        public:
        Pipeline();
        ~Pipeline()
        {
            CleanupQueue.Run();
        }

        std::vector<Shaders::EkShader*> Shaders;

        VertexType VT;

        PipeLayout PipelineLayout;

        // When messing with descriptors you do have to mess with the pipelinelayout in CreateGraphicsPipeline
        void CreateGraphicsPipeline(VkDevice* pDev, float Height, float Width, VkRenderPass* Renderpass, uint32_t SubpassToUse, PipeLayout* pLayout);

        std::vector<VkDescriptorSetLayout>* GetDescriptorLayouts();

        private:
        VkRenderPass* Renderpass;
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

    class PipeLayout
    {
        public:
        std::vector<VkDescriptorSetLayout> Descriptors;
        std::vector<VkPushConstantRange> PushConstants;
    };

}
