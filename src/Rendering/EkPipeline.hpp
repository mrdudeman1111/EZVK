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
    class PipelineResources
    {
        public:
        VkDescriptorPool DescriptorPool;
        std::vector<VkDescriptorSet> Descriptors;

        void CreateDescriptorPool(Pipeline* Pipe);
    }

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

        // When messing with descriptors you do have to mess with the pipelinelayout in CreateGraphicsPipeline
        void CreateGraphicsPipeline(VkDevice* Handle, float Height, float Width, VkRenderPass* Renderpass, uint32_t SubpassToUse);

        std::vector<VkDescriptorSetLayout>* GetDescriptorLayouts();

        private:
        VkRenderPass* Renderpass;
        VkPipeline VkPipe;
        VkPipelineLayout PipelineLayout;
        std::vector<VkDescriptorSetLayout> DescriptorLayouts;

        DeleteQueue CleanupQueue;
        VkViewport ViewPort;
    };
}
