#pragma once

#include <EkTypes.hpp>

#define Check(x)                                                 \
	do                                                              \
	{                                                               \
		VkResult err = x;                                           \
		if (err)                                                    \
		{                                                           \
			std::cout <<"Detected Vulkan error: " << err << std::endl; \
			abort();                                                \
		}                                                           \
	} while (0)

namespace Buffers
{
    void CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, AllocatedBuffer* AllocatedBuffer, VmaMemoryUsage MemUse);
}

namespace Mesh
{
    // glm::mat4 ConvertMat4(aiMatrix4x4 AssimpMatrix);
}

namespace InitHelpers
{
    void InitGlfw();

    void RequestLayer(const char* LayerName);

    void RequestExtension(const char* ExtensionName);

    void InitVMA();

    void CreateInstance();

    void PickPhysDev();

    void CreateSwapChain(VkDevice* Device, VkInstance* Instance);
}

namespace Pipeline
{
    // VkShaderModule CreateShaderModule(std::string& FileName);

    // VkWriteDescriptorSet WriteToDescriptor(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorBufferInfo* bufferInfo , uint32_t binding);

    // // When messing with descriptors you do have to mess with the pipelinelayout in CreateGraphicsPipeline
    // void CreateGraphicsPipeline();
}
