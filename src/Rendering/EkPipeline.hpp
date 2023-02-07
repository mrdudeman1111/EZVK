#pragma once

#include <Base/EkTypes.hpp>
#include <Rendering/EkRenderpass.hpp>

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
        std::vector<Shaders::EkShader*> Shaders;
        DeleteQueue CleanupQueue;
        VkPipeline Pipeline;

        Ek::Renderpass* Renderpass;

        VertexType VT;

        std::vector<VkDescriptorSetLayout> DescriptorLayouts;

        // When messing with descriptors you do have to mess with the pipelinelayout in CreateGraphicsPipeline
        void CreateGraphicsPipeline(float Height, float Width);

        VkWriteDescriptorSet WriteToDescriptor(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorBufferInfo* bufferInfo , uint32_t binding);

        private:
        VkPipelineLayout PipelineLayout;
        VkViewport ViewPort;
    };
}
