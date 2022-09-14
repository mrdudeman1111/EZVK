#pragma once

#include <EkTypes.hpp>

namespace Pipeline
{
    VkShaderModule CreateShaderModule(std::string& FileName);

    VkWriteDescriptorSet WriteToDescriptor(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorBufferInfo* bufferInfo , uint32_t binding);

    // When messing with descriptors you do have to mess with the pipelinelayout in CreateGraphicsPipeline
    void CreateGraphicsPipeline();
}