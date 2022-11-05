#pragma once

#include <EkTypes.hpp>
#include <EkRenderpass.hpp>

struct EkShader
{
    VkShaderModule ShaderModule;
    const char* Name;
    VkShaderStageFlagBits Stage;
};


class EkPipeline
{
    public:
    std::string VertPath, FragPath;
    VkDevice* DevicePtr;
    DeleteQueue CleanupQueue;
    VkExtent3D* ExtentPtr;

    std::vector<VkDescriptorSetLayout> DescriptorLayouts;
    std::vector<EkShader> Shaders;

    // When messing with descriptors you do have to mess with the pipelinelayout in CreateGraphicsPipeline
    void CreateGraphicsPipeline();
    VkWriteDescriptorSet WriteToDescriptor(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorBufferInfo* bufferInfo , uint32_t binding);

    private:
    VkPipelineLayout PipelineLayout;
    VkShaderModule CreateShaderModule(std::string& FileName);
    VkPipeline Pipeline;
    VkViewport ViewPort;
    Ek::Renderpass* RenderPass;
};
