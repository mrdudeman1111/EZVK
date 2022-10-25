#pragma once

#include <EkTypes.hpp>
#include <EkWindow.hpp>

struct EkShader
{
    VkShaderModule ShaderModule;
    const char* Name;
    VkShaderStageFlagBits Stage;
};

struct EkSubPass : VkSubpassDescription
{
    public:
    std::vector<AttDesc> Attachments;
    AttDesc DepthStencil;
    VkFormat RenderFormat;

    VkSubpassDescription Subpass;
    void Build(VkPipelineBindPoint BindPoint, std::vector<AttDesc>* Inputs, uint32_t InputSize = 0);
};

class EkRenderPass
{
    public:
    EkRenderPass()
    {

    };
    std::vector<RenderTarget> RenderTargets;
    std::vector<EkSubPass> Subpasses;
    VkRenderPass RenderPass;

    VkDevice* DevicePtr;
    
    VkFormat RenderFormat;
    VkSampleCountFlagBits Samples;

    void CreateRenderPass();
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
    EkRenderPass RenderPass;
};
