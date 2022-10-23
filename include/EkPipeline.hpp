#pragma once

#include <EkTypes.hpp>

struct EkShader
{
    VkShaderModule ShaderModule;
    const char* Name;
    VkShaderStageFlagBits Stage;
};

struct AttachmentRef : VkAttachmentReference
{
    public:
    RtType Type;
    VkImageLayout Layout;
};

struct EkSubPass
{
    public:

    std::vector<AttachmentRef> Attachments;
    AttachmentRef DepthStencil;
    VkFormat RenderFormat;

    VkSubpassDescription Subpass;
    void Build(VkPipelineBindPoint BindPoint, uint32_t InputSize, std::vector<uint32_t> Preserves, std::vector<AttachmentRef> Inputs);
};

class EkRenderPass
{
    public:
    EkRenderPass();
    std::vector<RenderTarget> RenderTargets;
    std::vector<EkSubPass> Subpasses;
    
    VkFormat RenderFormat;
    VkSampleCountFlagBits Samples;
    VkRenderPass RenderPass;

    void CreateRenderPass();
};

class EkPipeline
{
    public:
    std::string VertPath, FragPath;
    VkDevice* DevicePtr;
    DeleteQueue CleanupQueue;

    std::vector<VkDescriptorSetLayout> DescriptorLayouts;
    std::vector<EkShader> Shaders;

    // When messing with descriptors you do have to mess with the pipelinelayout in CreateGraphicsPipeline
    void CreateGraphicsPipeline(uint32_t width, uint32_t height);
    VkWriteDescriptorSet WriteToDescriptor(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorBufferInfo* bufferInfo , uint32_t binding);

    private:
    VkPipelineLayout PipelineLayout;
    VkShaderModule CreateShaderModule(std::string& FileName);
    VkPipeline Pipeline;
    VkViewport ViewPort;
    EkRenderPass RenderPass;
};
