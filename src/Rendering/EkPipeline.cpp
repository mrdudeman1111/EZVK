#include <Rendering/EkPipeline.hpp>

std::vector<char> ReadFile(std::string& FileName)
{
    std::ifstream file(FileName, std::ios::ate | std::ios::binary);

    if (!file.is_open ()) 
    {
        throw std::runtime_error ("failed to open file!");
    }

    size_t file_size = (size_t)file.tellg ();
    std::vector<char> buffer (file_size);

    file.seekg (0);
    file.read (buffer.data (), static_cast<std::streamsize> (file_size));

    file.close ();

    return buffer;
}

VkShaderModule Shaders::CreateShaderModule(std::string& FileName)
{
    std::vector<char> Code = ReadFile(FileName);
    VkShaderModuleCreateInfo Info = {};
    Info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    Info.codeSize = Code.size();
    Info.pCode = reinterpret_cast<const uint32_t*> (Code.data());

    VkShaderModule ShaderModule;
    auto Res = vkCreateShaderModule(GlobDevice, &Info, nullptr, &ShaderModule);
    if(Res != VK_SUCCESS)
    {
        std::cout << "Error: " << Res << std::endl;
        throw std::runtime_error("Failed to create a shadermodule");
    }
    return ShaderModule;
}

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
void Ek::Pipeline::CreateGraphicsPipeline(float Height, float Width)
{
    // 1
    std::vector<VkPipelineShaderStageCreateInfo> ShaderStages;
    for(const auto Shader : Shaders)
    {
        VkPipelineShaderStageCreateInfo ShaderInfo{};
        ShaderInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        ShaderInfo.stage = Shader->Stage;
        ShaderInfo.module = Shader->ShaderModule;
        ShaderInfo.pName = Shader->ShaderEntryPointName;
        ShaderStages.push_back(ShaderInfo);
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
        PipelineLayoutInfo.setLayoutCount = DescriptorLayouts.size();
        PipelineLayoutInfo.pSetLayouts = DescriptorLayouts.data();

        if(vkCreatePipelineLayout(GlobDevice, &PipelineLayoutInfo, nullptr, &PipelineLayout) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create pipeline layout!");
        }

        CleanupQueue([this](){ vkDestroyPipelineLayout(GlobDevice, PipelineLayout, nullptr); });

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

        DepthStencil.depthTestEnable = true ? VK_TRUE : VK_FALSE;
        DepthStencil.depthWriteEnable = true ? VK_TRUE : VK_FALSE;
        DepthStencil.depthCompareOp = true ? VK_COMPARE_OP_LESS_OR_EQUAL : VK_COMPARE_OP_ALWAYS;
        DepthStencil.depthBoundsTestEnable = VK_FALSE;
        DepthStencil.minDepthBounds = 0.0f; // Optional
        DepthStencil.maxDepthBounds = 1.0f; // Optional
        DepthStencil.stencilTestEnable = VK_FALSE;

    // 10
        VkGraphicsPipelineCreateInfo PipelineCreateInfo{};
        PipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        PipelineCreateInfo.stageCount = 2;
        PipelineCreateInfo.pStages = ShaderStages.data();
        PipelineCreateInfo.pVertexInputState = &VertInputInfo;
        PipelineCreateInfo.pInputAssemblyState = &InputAssembly;
        PipelineCreateInfo.pViewportState = &ViewportState;
        PipelineCreateInfo.pRasterizationState = &Rasterizer;
        PipelineCreateInfo.pMultisampleState = &MultiSampling;
        PipelineCreateInfo.pColorBlendState = &ColorBlendingState;
        PipelineCreateInfo.layout = PipelineLayout;
        PipelineCreateInfo.renderPass = Renderpass->RenderPass;
        PipelineCreateInfo.subpass = 0;
        PipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        PipelineCreateInfo.pDepthStencilState = &DepthStencil;

        //Make sure it's not a problem with the shaders. and that they've been compiled
        auto Error = vkCreateGraphicsPipelines(GlobDevice, VK_NULL_HANDLE, 1, &PipelineCreateInfo, nullptr, &Pipeline);
        if(Error != VK_SUCCESS)
        {
            std::cout << "Failed to create graphics pipeline! Error: " << Error << std::endl;
            throw std::runtime_error("failed to create graphics pipeline!");
        }

    // 11
        CleanupQueue([this](){ vkDestroyPipeline(GlobDevice, Pipeline, nullptr); });
}

VkWriteDescriptorSet Ek::Pipeline::WriteToDescriptor(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorBufferInfo* bufferInfo , uint32_t binding)
{
    VkWriteDescriptorSet write = {};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.pNext = nullptr;

    write.dstBinding = binding;
    write.dstSet = dstSet;
    write.descriptorCount = 1;
    write.descriptorType = type;
    write.pBufferInfo = bufferInfo;

    return write;
}