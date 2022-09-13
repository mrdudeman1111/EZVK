#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/string_cast.hpp>

#include <vk_mem_alloc.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <memory>
#include <fstream>
#include <chrono>
#include <cstdarg>
#include <array>
#include <iostream>
#include <vector>

namespace GlobalConstants
{
    // Vulkan/Glfw Basics
        extern VkDevice Device;
        extern VkInstance Instance;
        extern VkPhysicalDevice PhysDev;
        extern VkDebugUtilsMessengerEXT DebugMessenger;

    	extern VmaAllocator Allocator;

        extern GLFWwindow* Window;
        extern VkSurfaceKHR Surface;
        extern int Width;
        extern int Height;
    
	
    extern VkDescriptorSetLayout CameraLayout;
	extern VkDescriptorSetLayout SkeletalLayout;
    
    extern VkViewport Viewport;
        // Viewport.x = 0;
        // Viewport.y = 0;
        // Viewport.width = (float) PipelineInfo->Width;
        // Viewport.height = (float) PipelineInfo->Height;
        // Viewport.minDepth = 0.0f;
        // Viewport.maxDepth = 1.0f;
    extern VkViewport Viewport;
        // Viewport.x = 0;
        // Viewport.y = 0;
        // Viewport.width = (float) PipelineInfo->Width;
        // Viewport.height = (float) PipelineInfo->Height;
        // Viewport.minDepth = 0.0f;
        // Viewport.maxDepth = 1.0f;

    extern VkRect2D Scissor;
        // Scissor.offset = {0, 0};
        // Scissor.extent = VkExtent2D{(uint32_t) PipelineInfo->Width, (uint32_t) PipelineInfo->Height};

    extern VkPipelineViewportStateCreateInfo ViewportState;
        // ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        // ViewportState.viewportCount = 1;
        // ViewportState.pViewports = &GlobalConstants::Viewport;
        // ViewportState.scissorCount = 1;
        // ViewportState.pScissors = &Scissor;
}

void ThrowError(const char* Error);

// Types
    enum VertexType{VTX_Basic, VTX_Rigged};

    typedef uint32_t ivec3[3];


// Allocated Types:
    struct AllocatedBuffer
    {
        VkBuffer Buffer;
        VmaAllocation Allocation;
    };

    struct AllocatedImage
    {
        VkImage Image;
        VmaAllocation Allocation;
    };


// VkWrappers
    template<typename CmdArg>
    struct EkCommandBuffer
    {
        public:
        VkCommandBuffer CommandBuffer;
        void Submit();
        std::vector<CmdArg> Queue;
            // Always pass a lambda, This lambda should capture whatever you're calling this function from, and sould call all the vulkan API calls you want to make (These are VkCmdXXX such as VkCmdBeginRenderpass, VkCmdDraw, etc)
        void QueueCommand(CmdArg Function)
        {
            Queue.append(Function);
        }
    };

    // struct Pipeline
    // {
    //     public:

        // VkPipelineShaderStageCreateInfo BuildShaders()
        // {
        //     auto vertShaderCode = ReadFile(PipelineInfo->VertShaderPath);
        //     auto fragShaderCode = ReadFile(PipelineInfo->FragShaderPath);

        //     VkShaderModule VertShaderModule = CreateShaderModule(vertShaderCode, GlobalConstants::Device);
        //     VkShaderModule FragShaderModule = CreateShaderModule(fragShaderCode, GlobalConstants::Device);

        //     VkPipelineShaderStageCreateInfo VertShaderStage{};
        //     VertShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        //     VertShaderStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
        //     VertShaderStage.module = VertShaderModule;
        //     VertShaderStage.pName = "main";

        //     VkPipelineShaderStageCreateInfo FragShaderStage{};
        //     FragShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        //     FragShaderStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        //     FragShaderStage.module = FragShaderModule;
        //     FragShaderStage.pName = "main";

        //     VkPipelineShaderStageCreateInfo ShaderStages[2];
        //     ShaderStages[0] = VertShaderStage;
        //     ShaderStages[1] = FragShaderStage;

        //     return ShaderStages;
        // }

        // void Build(VertexType VertType)
        // {
        //     VkPipelineShaderStageCreateInfo* ShaderStages = BuildShaders();

        //     VkPipelineVertexInputStateCreateInfo VertInputInfo{};
        //     VertInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        //     std::vector<VkVertexInputBindingDescription> BindingDescription;
        //     std::vector<VkVertexInputAttributeDescription> AttributeDescription;
            
        //     if(VertType == VTX_Rigged)
        //     {
        //         BindingDescription = RiggedVertex::GetBindingDescription();
        //         AttributeDescription = RiggedVertex::GetAttributeDescription();
        //     }

        //     if(VertType == VTX_Basic)
        //     {
        //         BindingDescription = RiggedVertexVertex::GetBindingDescription();
        //         AttributeDescription = RiggedVertex::GetAttributeDescription();
        //     }

        //     VertInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(BindingDescription.size());
        //     VertInputInfo.pVertexBindingDescriptions = BindingDescription.data();
        //     VertInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(AttributeDescription.size());
        //     VertInputInfo.pVertexAttributeDescriptions = AttributeDescription.data();

        //     std::vector<VkDescriptorSetLayout> DescriptorLayouts (2);

        //     DescriptorLayouts[0] = GlobalConstants::CameraDescriptorLayout;
        //     DescriptorLayouts[1] = GlobalConstants::SkeletalDescriptorLayout;
            
        //     VkPipelineLayoutCreateInfo PipelineLayoutInfo{};
        //     PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        //     PipelineLayoutInfo.setLayoutCount = 2;
        //     PipelineLayoutInfo.pSetLayouts = DescriptorLayouts.data();

        //     //Make sure it's not a problem with the shaders. And that they've been compiled
        //     if(vkCreatePipelineLayout(GlobalConstants::Device, &PipelineLayoutInfo, nullptr, &PipelineInfo->PipelineLayout) != VK_SUCCESS) 
        //     {
        //         throw std::runtime_error("failed to create pipeline layout!");
        //     }

        //     VkPipelineInputAssemblyStateCreateInfo InputAssembly{};
        //     InputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        //     InputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        //     InputAssembly.primitiveRestartEnable = VK_FALSE;

        //     VkViewport Viewport{};
        //     Viewport.x = 0;
        //     Viewport.y = 0;
        //     Viewport.width = (float) PipelineInfo->Width;
        //     Viewport.height = (float) PipelineInfo->Height;
        //     Viewport.minDepth = 0.0f;
        //     Viewport.maxDepth = 1.0f;

        //     VkRect2D Scissor{};
        //     Scissor.offset = {0, 0};
        //     Scissor.extent = VkExtent2D{(uint32_t) PipelineInfo->Width, (uint32_t) PipelineInfo->Height};

        //     VkPipelineViewportStateCreateInfo ViewportState{};
        //     ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        //     ViewportState.viewportCount = 1;
        //     ViewportState.pViewports = &Viewport;
        //     ViewportState.scissorCount = 1;
        //     ViewportState.pScissors = &Scissor;

        //     VkPipelineRasterizationStateCreateInfo Rasterizer{};
        //     Rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        //     Rasterizer.depthClampEnable = VK_FALSE;
        //     Rasterizer.rasterizerDiscardEnable = VK_FALSE;
        //     Rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        //     Rasterizer.lineWidth = 1.0f;
        //     Rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        //     Rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        //     Rasterizer.depthBiasEnable = VK_FALSE;

        //     VkPipelineMultisampleStateCreateInfo MultiSampling{};
        //     MultiSampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        //     MultiSampling.sampleShadingEnable = VK_FALSE;
        //     MultiSampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        //     VkPipelineColorBlendAttachmentState ColorBlendAttachment{};
        //     ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        //     ColorBlendAttachment.blendEnable = VK_FALSE;

        //     VkPipelineColorBlendStateCreateInfo ColorBlendingState{};
        //     ColorBlendingState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        //     ColorBlendingState.logicOpEnable = VK_FALSE;
        //     ColorBlendingState.logicOp = VK_LOGIC_OP_COPY;
        //     ColorBlendingState.attachmentCount = 1;
        //     ColorBlendingState.pAttachments = &ColorBlendAttachment;
        //     ColorBlendingState.blendConstants[0] = 0.0f;
        //     ColorBlendingState.blendConstants[1] = 0.0f;
        //     ColorBlendingState.blendConstants[2] = 0.0f;
        //     ColorBlendingState.blendConstants[3] = 0.0f;

        //     //Create Depth Stencil State
        //     VkPipelineDepthStencilStateCreateInfo DepthStencil = {};
        //     DepthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        //     DepthStencil.pNext = nullptr;

        //     DepthStencil.depthTestEnable = true ? VK_TRUE : VK_FALSE;
        //     DepthStencil.depthWriteEnable = true ? VK_TRUE : VK_FALSE;
        //     DepthStencil.depthCompareOp = true ? VK_COMPARE_OP_LESS_OR_EQUAL : VK_COMPARE_OP_ALWAYS;
        //     DepthStencil.depthBoundsTestEnable = VK_FALSE;
        //     DepthStencil.minDepthBounds = 0.0f; // Optional
        //     DepthStencil.maxDepthBounds = 1.0f; // Optional
        //     DepthStencil.stencilTestEnable = VK_FALSE;

        //     VkGraphicsPipelineCreateInfo PipelineCreateInfo{};
        //     PipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        //     PipelineCreateInfo.stageCount = 2;
        //     PipelineCreateInfo.pStages = ShaderStages;
        //     PipelineCreateInfo.pVertexInputState = &VertInputInfo;
        //     PipelineCreateInfo.pInputAssemblyState = &InputAssembly;
        //     PipelineCreateInfo.pViewportState = &ViewportState;
        //     PipelineCreateInfo.pRasterizationState = &Rasterizer;
        //     PipelineCreateInfo.pMultisampleState = &MultiSampling;
        //     PipelineCreateInfo.pColorBlendState = &ColorBlendingState;
        //     PipelineCreateInfo.layout = PipelineInfo->PipelineLayout;
        //     PipelineCreateInfo.renderPass = PipelineInfo->RenderPass;
        //     PipelineCreateInfo.subpass = 0;
        //     PipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        //     PipelineCreateInfo.pDepthStencilState = &DepthStencil;

        //     VkSwapchainKHR SwapChains[] = { *PipelineInfo->SwapChain };
            
        //     //Make sure it's not a problem with the shaders. and that they've been compiled
        //     auto Error = vkCreateGraphicsPipelines(GlobalConstants::Device, VK_NULL_HANDLE, 1, &PipelineCreateInfo, nullptr, &PipelineInfo->GraphicsPipeline);
        //     if(Error != VK_SUCCESS)
        //     {
        //         std::cout << "Failed to create graphics pipeline! Error: " << Error << std::endl;
        //         throw std::runtime_error("failed to create graphics pipeline!");
        //     }

        //     vkDestroyShaderModule(GlobalConstants::Device, FragShaderModule, nullptr);
        //     vkDestroyShaderModule(GlobalConstants::Device, VertShaderModule, nullptr);
        // }
    // };


// Vertices:
    struct BasicVertex
    {
        public:
            alignas(16) glm::vec3 Position = glm::vec3(0.0f);
            alignas(16) glm::vec3 Color = glm::vec3(1.0f);
            alignas(16) glm::vec3 Normal = glm::vec3(0.0f);

            static std::vector<VkVertexInputBindingDescription> GetBindingDescription()
            {
                std::vector<VkVertexInputBindingDescription> BindingDescription(1);
                BindingDescription[0].binding = 0;
                BindingDescription[0].stride = sizeof(BasicVertex);
                BindingDescription[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

                return BindingDescription;
            }

            static std::vector<VkVertexInputAttributeDescription> GetAttributeDescription()
            {
                std::vector<VkVertexInputAttributeDescription> AttributeDescription(3);
                AttributeDescription[0].binding = 0;
                AttributeDescription[0].location = 0;
                AttributeDescription[0].format = VK_FORMAT_R32G32B32_SFLOAT;
                AttributeDescription[0].offset = offsetof(BasicVertex, Position);

                AttributeDescription[1].binding = 0;
                AttributeDescription[1].location = 1;
                AttributeDescription[1].format = VK_FORMAT_R32G32B32_SFLOAT;
                AttributeDescription[1].offset = offsetof(BasicVertex, Color);
                
                AttributeDescription[2].binding = 0;
                    AttributeDescription[2].location = 2;
                    AttributeDescription[2].format = VK_FORMAT_R32G32B32_SFLOAT;
                    AttributeDescription[2].offset = offsetof(BasicVertex, Normal);

                return AttributeDescription;
            }
    };

    struct RiggedVertex
    {
        public:
        alignas(16) glm::vec3 Position = glm::vec3(0.0f);
        alignas(16) glm::vec3 Color = glm::vec3(1.0f);
        alignas(16) glm::vec3 Normal = glm::vec3(0.0f);
        alignas(16) ivec3 BoneIDs = {99, 99, 99};
        alignas(16) glm::vec3 BoneWeights = {0, 0, 0};
        uint16_t BoneIDIterator = 0;
        uint16_t BoneWeightIterator = 0;

        void AddBoneID(unsigned int ID)
        {
            if(BoneIDIterator < 3)
            {
                BoneIDs[BoneIDIterator] = ID;
                BoneIDIterator++;
            }
            else
            {
                std::cout << "Error: Too many bone IDs in a vertex" << std::endl;
            }
        }

        void AddBoneWeight(float Weight)
        {
            if(BoneWeightIterator < 3)
            {
                BoneWeights[BoneWeightIterator] = Weight;
                BoneWeightIterator++;
            }
            else
            {
                std::cout << "Error: Too many bone weights in a vertex" << std::endl;
            }
        }

        static std::vector<VkVertexInputBindingDescription> GetBindingDescription()
        {
            std::vector<VkVertexInputBindingDescription> BindingDescription(1);
            BindingDescription[0].binding = 0;
            BindingDescription[0].stride = sizeof(RiggedVertex);
            BindingDescription[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return BindingDescription;
        }

        // IT IS IMPORTANT TO CHANGE THIS WHEN CHANGING THE VERTEX STRUCT OR ADDING ATTRIBUTES
        static std::vector<VkVertexInputAttributeDescription> GetAttributeDescription()
        {
            std::vector<VkVertexInputAttributeDescription> AttributeDescription(5);
            AttributeDescription[0].binding = 0;
            AttributeDescription[0].location = 0;
            AttributeDescription[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            AttributeDescription[0].offset = offsetof(RiggedVertex, Position);

            AttributeDescription[1].binding = 0;
            AttributeDescription[1].location = 1;
            AttributeDescription[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            AttributeDescription[1].offset = offsetof(RiggedVertex, Color);

            AttributeDescription[2].binding = 0;
            AttributeDescription[2].location = 2;
            AttributeDescription[2].format = VK_FORMAT_R32G32B32_SFLOAT;
            AttributeDescription[2].offset = offsetof(RiggedVertex, Normal);

            AttributeDescription[3].binding = 0;
            AttributeDescription[3].location = 3;
            AttributeDescription[3].format = VK_FORMAT_R32G32B32_UINT;
            AttributeDescription[3].offset = offsetof(RiggedVertex, BoneIDs);

            AttributeDescription[4].binding = 0;
            AttributeDescription[4].location = 4;
            AttributeDescription[4].format = VK_FORMAT_R32G32B32_SFLOAT;
            AttributeDescription[4].offset = offsetof(RiggedVertex, BoneWeights);

            return AttributeDescription;
        }
    };

    struct ProcessedRiggedVertex
    {
        alignas(16) glm::vec3 Position;
        alignas(16) glm::vec3 Color;
        alignas(16) glm::vec3 Normal;
        alignas(16) ivec3 BoneIDs;
        alignas(16) glm::vec3 BoneWeights;
    };

    struct ProcessedBasicVertex
    {
        alignas(16) glm::vec3 Position;
        alignas(16) glm::vec3 Color;
        alignas(16) glm::vec3 Normal;
    };


