#include <Rendering/EkPipeline.hpp>

/*
    1: Create Stages for shaders via VkPipelineShaderStageCreateInfo and wrap them into a vector
    
    2: Grab Vertex InputBindings and InputAttributes

    3: Setup VertexInput Via VkPipelineVertexInputStageCreateInfo Using the InputBindings and InputAttributes

    4: Make The PipelineLayoutInfo with DescriptorLayouts
    
    5: Setup Primitive assembly (read more about that topic here: https://docs.tizen.org/application/native/guides/graphics/assembly ) to sum it up, it takes all the vertex positions on the screen, and makes a "face" out of it

    6: Setup a viewport

    7: Setup a vulkan rasterizer

    8: Setup smoothing stages ( MSAA, Color Blending, etc )

    9: Create a Depth Stencil state ( it's a face culling attachment, essentially you attach it to a pipeline and the pipeline uses it to ensure that you can't see faces through other faces )

    10: Create The pipeline With all attachment, viewport, vertex, shader, and depth information

    11: cleanup
*/

// When messing with descriptors you do have to mess with the pipelinelayout in CreateGraphicsPipeline
void Ek::Pipeline::Build(uint32_t SubpassToUse)
{
    // 1
        std::vector<VkPipelineShaderStageCreateInfo> ShaderStages;
        std::vector<VkDescriptorSetLayout> ShaderLayouts;
        for(const auto Shader : Shaders)
        {
            VkPipelineShaderStageCreateInfo ShaderInfo{};
            ShaderInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            ShaderInfo.stage = Shader->Stage;
            ShaderInfo.module = Shader->ShaderModule;
            ShaderInfo.pName = Shader->ShaderEntryPoint;
            ShaderStages.push_back(ShaderInfo);

            ShaderLayouts.insert(ShaderLayouts.end(), Shader->DescriptorLayouts.begin(), Shader->DescriptorLayouts.end());
        }

        ShaderStages.shrink_to_fit();

    // 2
        std::vector<VkVertexInputBindingDescription> BindingDescription;
        std::vector<VkVertexInputAttributeDescription> AttributeDescription;
        if(VT = VertexType::VTX_Rigged)
        {
            BindingDescription.resize(1);
            BindingDescription = RiggedVertex::GetBindingDescription();
            AttributeDescription.resize(5);
            AttributeDescription = RiggedVertex::GetAttributeDescription();
        }
        else
        {
            BindingDescription.resize(1);
            BindingDescription = BasicVertex::GetBindingDescription();
            AttributeDescription.resize(3);
            AttributeDescription = BasicVertex::GetAttributeDescription();
        }

    // 3
        VkPipelineVertexInputStateCreateInfo VertInputInfo{};
        VertInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        VertInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(BindingDescription.size());
        VertInputInfo.pVertexBindingDescriptions = BindingDescription.data();
        VertInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(AttributeDescription.size());
        VertInputInfo.pVertexAttributeDescriptions = AttributeDescription.data();

    // 4
        VkPipelineLayoutCreateInfo PipelineLayoutInfo{};
        PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        PipelineLayoutInfo.setLayoutCount = ShaderLayouts.size();
        PipelineLayoutInfo.pSetLayouts = ShaderLayouts.data();
            
            // Add Push Constants to EkShader.
        // PipelineLayoutInfo.pushConstantRangeCount = .size();
        // PipelineLayoutInfo.pPushConstantRanges = .data();

        if(vkCreatePipelineLayout(*p_Dev, &PipelineLayoutInfo, nullptr, &VkPipeLayout) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create pipeline layout!");
        }

        VkDevice* DevHandle = p_Dev;
        CleanupQueue([this, DevHandle](){ vkDestroyPipelineLayout(*DevHandle, VkPipeLayout, nullptr); });

    // 5
        VkPipelineInputAssemblyStateCreateInfo InputAssembly{};
        InputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        InputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        InputAssembly.primitiveRestartEnable = VK_FALSE;

    // 6
        VkViewport Viewport{};
        Viewport.x = 0;
        Viewport.y = 0;
        Viewport.width = Width;
        Viewport.height = Height;
        Viewport.minDepth = 0.0f;
        Viewport.maxDepth = 1.0f;

        VkRect2D Scissor{};
        Scissor.offset = {0, 0};
        Scissor.extent = VkExtent2D{ (uint32_t)Width, (uint32_t)Height };

        VkPipelineViewportStateCreateInfo ViewportState{};
        ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        ViewportState.viewportCount = 1;
        ViewportState.pViewports = &Viewport;
        ViewportState.scissorCount = 1;
        ViewportState.pScissors = &Scissor;

    // 7
        VkPipelineRasterizationStateCreateInfo Rasterizer{};
        Rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        Rasterizer.depthClampEnable = VK_FALSE;
        Rasterizer.rasterizerDiscardEnable = VK_FALSE;
        Rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        Rasterizer.lineWidth = 1.0f;
        Rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        Rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        Rasterizer.depthBiasEnable = VK_FALSE;

    // 8
        VkPipelineMultisampleStateCreateInfo MultiSampling{};
        MultiSampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        MultiSampling.sampleShadingEnable = VK_FALSE;
        MultiSampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

        VkPipelineColorBlendAttachmentState ColorBlendAttachment{};
        ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        ColorBlendAttachment.blendEnable = VK_FALSE;

        VkPipelineColorBlendStateCreateInfo ColorBlendingState{};
        ColorBlendingState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        ColorBlendingState.logicOpEnable = VK_FALSE;
        ColorBlendingState.logicOp = VK_LOGIC_OP_COPY;
        ColorBlendingState.attachmentCount = 1;
        ColorBlendingState.pAttachments = &ColorBlendAttachment;
        ColorBlendingState.blendConstants[0] = 0.0f;
        ColorBlendingState.blendConstants[1] = 0.0f;
        ColorBlendingState.blendConstants[2] = 0.0f;
        ColorBlendingState.blendConstants[3] = 0.0f;

    // 9
        //Create Depth Stencil State
        VkPipelineDepthStencilStateCreateInfo DepthStencil = {};
        DepthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        DepthStencil.pNext = nullptr;

        DepthStencil.depthTestEnable = VK_TRUE;
        DepthStencil.depthWriteEnable = VK_TRUE;
        DepthStencil.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
        DepthStencil.depthBoundsTestEnable = VK_FALSE;
        DepthStencil.minDepthBounds = 0.0f; // Optional
        DepthStencil.maxDepthBounds = 1.0f; // Optional
        DepthStencil.stencilTestEnable = VK_FALSE;

    // 10
        VkGraphicsPipelineCreateInfo PipelineCreateInfo{};
        PipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        PipelineCreateInfo.stageCount = ShaderStages.size();
        PipelineCreateInfo.pStages = ShaderStages.data();
        PipelineCreateInfo.pVertexInputState = &VertInputInfo;
        PipelineCreateInfo.pInputAssemblyState = &InputAssembly;
        PipelineCreateInfo.pViewportState = &ViewportState;
        PipelineCreateInfo.pRasterizationState = &Rasterizer;
        PipelineCreateInfo.pMultisampleState = &MultiSampling;
        PipelineCreateInfo.pColorBlendState = &ColorBlendingState;
        PipelineCreateInfo.layout = VkPipeLayout;
        PipelineCreateInfo.renderPass = *p_Renderpass;
        PipelineCreateInfo.subpass = SubpassToUse;
        PipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        PipelineCreateInfo.pDepthStencilState = &DepthStencil;

        //Make sure it's not a problem with the shaders. and that they've been compiled
        auto Error = vkCreateGraphicsPipelines(*p_Dev, VK_NULL_HANDLE, 1, &PipelineCreateInfo, nullptr, &VkPipe);
        if(Error != VK_SUCCESS)
        {
            std::cout << "Failed to create graphics pipeline! Error: " << Error << std::endl;
            throw std::runtime_error("failed to create graphics pipeline!");
        }

    // 11
        CleanupQueue([this, DevHandle](){ vkDestroyPipeline(*DevHandle, VkPipe, nullptr); });
}

void Ek::Shader::AddShaderInput(VkDevice* pDev, uint32_t Location, VkDescriptorType Type, uint32_t InputCount)
{
    p_Dev = pDev;
    VkDescriptorPoolSize InputSize;
    InputSize.descriptorCount = InputCount;
    InputSize.type = Type;
    PoolSizes.push_back(InputSize);

    VkDescriptorSetLayoutBinding LayoutBinding;
    LayoutBinding.binding = Location;
    LayoutBinding.descriptorType = Type;
    LayoutBinding.stageFlags = Stage;
    LayoutBinding.descriptorCount = InputCount;

    DescriptorBindings.push_back(LayoutBinding);

    VkDescriptorSetLayoutCreateInfo LayoutInf;
    LayoutInf.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    LayoutInf.bindingCount = 1;
    LayoutInf.pBindings = &LayoutBinding;

    if(vkCreateDescriptorSetLayout(*p_Dev, &LayoutInf, nullptr, &DescriptorLayouts[LayoutIterator]) != VK_SUCCESS)
    {
        ThrowError("Failed to add Shader Input(s)\n");
    }

    LayoutIterator++;
    return;
}

void Ek::Shader::BuildShaderLayout()
{
    VkDescriptorPoolCreateInfo PoolInf;
    PoolInf.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    PoolInf.poolSizeCount = PoolSizes.size();
    PoolInf.pPoolSizes = PoolSizes.data();
    PoolInf.maxSets = DescriptorBindings.size();

    if(vkCreateDescriptorPool(*p_Dev, &PoolInf, nullptr, &DescriptorPool) != VK_SUCCESS)
    {
        ThrowError("Failed to create descriptor pool\n");
    }

    for(uint32_t i = 0; i < DescriptorBindings.size(); i++)
    {
        VkDescriptorSetAllocateInfo AllocInf;
        AllocInf.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        AllocInf.descriptorPool = DescriptorPool;
        AllocInf.descriptorSetCount = DescriptorLayouts.size();
        AllocInf.pSetLayouts = DescriptorLayouts.data();

        if(vkAllocateDescriptorSets(*p_Dev, &AllocInf, &DescriptorSets[i]) != VK_SUCCESS)
        {
            ThrowError("Failed to allocate some Descriptors");
        }
    }

    return;
}
