#include <EkPipeline.hpp>

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

VkShaderModule EkPipeline::CreateShaderModule(std::string& FileName)
{
    std::vector<char> Code = ReadFile(FileName);
    VkShaderModuleCreateInfo Info = {};
    Info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    Info.codeSize = Code.size();
    Info.pCode = reinterpret_cast<const uint32_t*> (Code.data());

    VkShaderModule ShaderModule;
    auto Res = vkCreateShaderModule(*DevicePtr, &Info, nullptr, &ShaderModule);
    if(Res != VK_SUCCESS)
    {
        std::cout << "Error: " << Res << std::endl;
        throw std::runtime_error("Failed to create a shadermodule");
    }
    return ShaderModule;
}

/*
    1: Read Shader Files into Spir-V ShaderModules
    
    2: Create Stages for shaders via VkPipelineShaderStageCreateInfo and wrap them into a vector
    
    3: Grab Vertex InputBindings and InputAttributes

    4: Setup VertexInput Via VkPipelineVertexInputStageCreateInfo Using the InputBindings and InputAttributes

    5: Make The PipelineLayoutInfo with DescriptorLayouts
    
    6: Setup Primitive assembly (read more about that topic here: https://docs.tizen.org/application/native/guides/graphics/assembly ) to sum it up, it takes all the vertex positions on the screen, and makes a "face" out of it

    7: Setup a viewport

    8: Setup a vulkan rasterizer

    9: Setup smoothing stages ( MSAA, Color Blending, etc )

    10: Create a Depth Stencil ( it's a face culling attachment, essentially you attach it to a pipeline and the pipeline uses it to ensure that you can't see faces through other faces )

    11: Create The pipeline With all attachment, viewport, vertex, shader, and depth information

    12: cleanup
*/

// When messing with descriptors you do have to mess with the pipelinelayout in CreateGraphicsPipeline
void EkPipeline::CreateGraphicsPipeline(uint32_t width, uint32_t height)
{
    // 1
        VkShaderModule VertShaderModule = CreateShaderModule(VertPath);
        VkShaderModule FragShaderModule = CreateShaderModule(FragPath);

    // 2
    std::vector<VkPipelineShaderStageCreateInfo> ShaderStages;
    for(const auto Shader : Shaders)
    {
        VkPipelineShaderStageCreateInfo ShaderInfo{};
        ShaderInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        ShaderInfo.stage = Shader.Stage;
        ShaderInfo.module = Shader.ShaderModule;
        ShaderInfo.pName = Shader.Name;
        ShaderStages.push_back(ShaderInfo);
    }
    ShaderStages.shrink_to_fit();

    // 3
        std::vector<VkVertexInputBindingDescription> BindingDescription(1);
        BindingDescription = RiggedVertex::GetBindingDescription();
        std::vector<VkVertexInputAttributeDescription> AttributeDescription(5);
        AttributeDescription = RiggedVertex::GetAttributeDescription();

    // 4
        VkPipelineVertexInputStateCreateInfo VertInputInfo{};
        VertInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        VertInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(BindingDescription.size());
        VertInputInfo.pVertexBindingDescriptions = BindingDescription.data();
        VertInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(AttributeDescription.size());
        VertInputInfo.pVertexAttributeDescriptions = AttributeDescription.data();

    // 5
        VkPipelineLayoutCreateInfo PipelineLayoutInfo{};
        PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        PipelineLayoutInfo.setLayoutCount = 2;
        PipelineLayoutInfo.pSetLayouts = DescriptorLayouts.data();

        if(vkCreatePipelineLayout(*DevicePtr, &PipelineLayoutInfo, nullptr, &PipelineLayout) != VK_SUCCESS) 
        {
            throw std::runtime_error("failed to create pipeline layout!");
        }

        CleanupQueue([this](){ vkDestroyPipelineLayout(*DevicePtr, PipelineLayout, nullptr); });

    // 6
        VkPipelineInputAssemblyStateCreateInfo InputAssembly{};
        InputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        InputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        InputAssembly.primitiveRestartEnable = VK_FALSE;

    // 7
        VkViewport Viewport{};
        Viewport.x = 0;
        Viewport.y = 0;
        Viewport.width = (float) width;
        Viewport.height = (float) height;
        Viewport.minDepth = 0.0f;
        Viewport.maxDepth = 1.0f;

        VkRect2D Scissor{};
        Scissor.offset = {0, 0};
        Scissor.extent = VkExtent2D{ (uint32_t) Window->ImageExtents.width, (uint32_t) Window->ImageExtents.height };

        VkPipelineViewportStateCreateInfo ViewportState{};
        ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        ViewportState.viewportCount = 1;
        ViewportState.pViewports = &Viewport;
        ViewportState.scissorCount = 1;
        ViewportState.pScissors = &Scissor;

    // 8
        VkPipelineRasterizationStateCreateInfo Rasterizer{};
        Rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        Rasterizer.depthClampEnable = VK_FALSE;
        Rasterizer.rasterizerDiscardEnable = VK_FALSE;
        Rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        Rasterizer.lineWidth = 1.0f;
        Rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        Rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        Rasterizer.depthBiasEnable = VK_FALSE;

    // 9
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

    // 10
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

    // 11
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
        PipelineCreateInfo.renderPass = RenderPass.;
        PipelineCreateInfo.subpass = 0;
        PipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        PipelineCreateInfo.pDepthStencilState = &DepthStencil;

        VkSwapchainKHR SwapChains[] = { *Window->Swapchain };
        
        //Make sure it's not a problem with the shaders. and that they've been compiled
        auto Error = vkCreateGraphicsPipelines(*DevicePtr, VK_NULL_HANDLE, 1, &PipelineCreateInfo, nullptr, &Pipeline);
        if(Error != VK_SUCCESS)
        {
            std::cout << "Failed to create graphics pipeline! Error: " << Error << std::endl;
            throw std::runtime_error("failed to create graphics pipeline!");
        }

    // 12
        CleanupQueue([this](){ vkDestroyPipeline(*DevicePtr, Pipeline, nullptr); });

        vkDestroyShaderModule(*DevicePtr, FragShaderModule, nullptr);
        vkDestroyShaderModule(*DevicePtr, VertShaderModule, nullptr);
}

void EkSubPass::Build(VkPipelineBindPoint BindPoint, uint32_t InputSize = 0, std::vector<uint32_t> PreserveAttachments, std::vector<AttachmentRef> Inputs)
{
    std::vector<AttachmentRef*> Colors, Depths, Resolves, Preserves;
    for(auto& Attachment : Attachments)
    {
        switch(Attachment.Type)
        {
            case RtColor:
                Colors.push_back(&Attachment);
                break;
            case RtDepth:
                Warn("Can not pass depth stencil in a subpass' attachments, it must be assigned to the DepthStencil member");
                break;
            case RtResolve:
                Resolves.push_back(&Attachment);
                break;
            case RtPreserve:
                Preserves.push_back(&Attachment);
                break;
            case RtColor | RtResolve | RtPreserve:
                Preserves.push_back(&Attachment);
                Colors.push_back(&Attachment);
                break;
            case RtColor | RtResolve:
                
            default:
                Warn("Uknown attachment is connected to a subpass");
                break;
        }
    }

    Subpass.pipelineBindPoint = BindPoint;
    Subpass.inputAttachmentCount = InputSize;
    Subpass.pInputAttachments = Inputs.data();
    Subpass.colorAttachmentCount = Colors.size();
    Subpass.pColorAttachments = *Colors.data();
    Subpass.pDepthStencilAttachment = &DepthStencil;
    Subpass.preserveAttachmentCount = Preserves.size();
    Subpass.pPreserveAttachments = PreserveAttachments.data();
    Subpass.pResolveAttachments = *Resolves.data();
}

void EkRenderPass::CreateRenderPass()
{
    std::vector<VkAttachmentDescription> AttachmentRefs(RenderTargets.size());
    for(uint i = 0; i < RenderTargets.size(); i++)
    {
        AttachmentRefs.push_back(RenderTargets[i].RenderTarget);
    }

    VkRenderPassCreateInfo RPInfo{};
    RPInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    RPInfo.pNext = nullptr;
    RPInfo.attachmentCount = AttachmentRefs.size();
    RPInfo.pAttachments = AttachmentRefs.data();

}

VkWriteDescriptorSet EkPipeline::WriteToDescriptor(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorBufferInfo* bufferInfo , uint32_t binding)
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
