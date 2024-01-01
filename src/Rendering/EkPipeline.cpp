#include "Base/EkTypes.hpp"
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

// Move VertexClass to material
void Ek::Pipeline::Build(Material* Mat, uint32_t SubpassToUse, Ek::BasicVertex* VertexClass)
{
    // 1
            // Add Push Constants to Ek::Material.
        // PipelineLayoutInfo.pushConstantRangeCount = .size();
        // PipelineLayoutInfo.pPushConstantRanges = .data();

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
        PipelineCreateInfo.stageCount = Mat->ShaderStages.size();
        PipelineCreateInfo.pStages = Mat->ShaderStages.data();
        PipelineCreateInfo.pVertexInputState = &Mat->VertexInput;
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
        auto Error = vkCreateGraphicsPipelines(*p_Dev, nullptr, 1, &PipelineCreateInfo, nullptr, &VkPipe);
        if(Error != VK_SUCCESS)
        {
            std::cout << "Failed to create graphics pipeline! Error: " << Error << std::endl;
            throw std::runtime_error("failed to create graphics pipeline!");
        }
    // 11
        CleanupQueue([this](){ vkDestroyPipeline(*p_Dev, VkPipe, nullptr); });
}

void Ek::Shader::AddImage(uint32_t Binding, VkDescriptorType Type, AllocatedImage* Image, uint32_t DescriptorCount)
{
    // Size of the "hole" in our shader to shove input through.
    VkDescriptorPoolSize InputSize{};
    InputSize.descriptorCount = DescriptorCount;
    InputSize.type = Type;
    PoolSizes.push_back(InputSize);

    // Layout, Binding, and general position info, relative to the shader
    VkDescriptorSetLayoutBinding LayoutBinding{};
    LayoutBinding.binding = Binding;
    LayoutBinding.descriptorType = Type;
    LayoutBinding.stageFlags = Stage;
    LayoutBinding.descriptorCount = DescriptorCount;

    DescriptorBindings.push_back(LayoutBinding);

    // The info for the descriptor
    VkDescriptorSetLayoutCreateInfo LayoutInf{};
    LayoutInf.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    LayoutInf.bindingCount = 1;
    LayoutInf.pBindings = &LayoutBinding;

    DescriptorLayouts.push_back({});

    if(vkCreateDescriptorSetLayout(*pDev, &LayoutInf, nullptr, &DescriptorLayouts[LayoutIterator]) != VK_SUCCESS)
    {
        ThrowError("Failed to add Shader Input(s)\n");
    }

    Images.push_back(Image);

    LayoutIterator++;
    return;
}

void Ek::Shader::AddBuffer(uint32_t Binding, VkDescriptorType Type, VkBuffer* Buffer, uint32_t DescriptorCount)
{
    VkDescriptorPoolSize InputSize{};
    InputSize.descriptorCount = DescriptorCount;
    InputSize.type = Type;
    PoolSizes.push_back(InputSize);

    VkDescriptorSetLayoutBinding LayoutBinding{};
    LayoutBinding.binding = Binding;
    LayoutBinding.descriptorType = Type;
    LayoutBinding.descriptorCount = DescriptorCount;
    LayoutBinding.stageFlags = Stage;

    DescriptorBindings.push_back(LayoutBinding);

    VkDescriptorSetLayoutCreateInfo LayoutInf{};
    LayoutInf.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    LayoutInf.bindingCount = DescriptorCount;
    LayoutInf.pBindings = &LayoutBinding;

    DescriptorLayouts.push_back({});

    if(vkCreateDescriptorSetLayout(*pDev, &LayoutInf, nullptr, &DescriptorLayouts[LayoutIterator]) != VK_SUCCESS)
    {
        ThrowError("Failed to add Shader Input(s)\n");
    }

    Buffers.push_back(Buffer);

    LayoutIterator++;
    return;
}

// void Ek::Shader::BuildShaderLayout()
// {
    // VkDescriptorPoolCreateInfo PoolInf;
    // PoolInf.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    // PoolInf.poolSizeCount = PoolSizes.size();
    // PoolInf.pPoolSizes = PoolSizes.data();
    // PoolInf.maxSets = DescriptorBindings.size();


    // for(uint32_t i = 0; i < DescriptorBindings.size(); i++)
    // {
    //     VkDescriptorSetAllocateInfo AllocInf;
    //     AllocInf.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    //     AllocInf.descriptorPool = DescriptorPool;
    //     AllocInf.descriptorSetCount = DescriptorLayouts.size();
    //     AllocInf.pSetLayouts = DescriptorLayouts.data();

    //     if(vkAllocateDescriptorSets(*p_Dev, &AllocInf, &DescriptorSets[i]) != VK_SUCCESS)
    //     {
    //         ThrowError("Failed to allocate some Descriptors");
    //     }
    // }

//     return;
// }

Ek::Material::Material(VkDevice* Device)
{
    pDev = Device;
}

void Ek::Material::AddShader(Ek::Shader* Shader)
{
    Shaders.push_back(*Shader);
}

void Ek::Material::AddShaderInput(ShaderType ShaderType, uint32_t Location, VkDescriptorType DescriptorType, void* Input, uint32_t DescriptorCount)
{
    AllocatedImage* Image = static_cast<AllocatedImage*>(Input);
    if(Image->Type)
    {
        for(int i = 0; i < Shaders.size(); i++)
        {
            if(Shaders[i].Type == ShaderType)
            {
                Shaders[i].AddImage(Location, DescriptorType, Image, DescriptorCount);
                return;
            }
        }
    }
    VkBuffer* Buffer = static_cast<VkBuffer*>(Input);
    if(Buffer)
    {
        for(int i = 0; i < Shaders.size(); i++)
        {
            if(Shaders[i].Type == ShaderType)
            {
                Shaders[i].AddBuffer(Location, DescriptorType, Buffer, DescriptorCount);
                return;
            }
        }
    }

    throw std::runtime_error("Failed to resolve Input");
}

void Ek::Material::Build(Ek::BasicVertex* VertexClass)
{
    pVertexClass = VertexClass;
    // PIPELINE/SHADERS LAYOUT

        // Layout bindings aren't needed, they are included inside the layout object.
        std::vector<VkDescriptorPoolSize> PoolSizes{};

        for(Shader& Sh : Shaders)
        {
            PoolSizes.insert(PoolSizes.end(), Sh.PoolSizes.begin(), Sh.PoolSizes.end());
            Layouts.insert(Layouts.end(), Sh.DescriptorLayouts.begin(), Sh.DescriptorLayouts.end());
        }

        VkDescriptorPoolCreateInfo PoolInf{};
        PoolInf.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        PoolInf.poolSizeCount = PoolSizes.size();
        PoolInf.pPoolSizes = PoolSizes.data();
        PoolInf.maxSets = PoolSizes.size();

        if(vkCreateDescriptorPool(*pDev, &PoolInf, nullptr, &DescriptorPool) != VK_SUCCESS)
        {
            throw std::runtime_error("Failed to create Descriptor Pool For a material");
        }

        for(int i = 0; i < Layouts.size(); i++)
        {
            VkDescriptorSetAllocateInfo AllocInfo{};
            AllocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
            AllocInfo.descriptorPool = DescriptorPool;
            AllocInfo.descriptorSetCount = 1;
            AllocInfo.pSetLayouts = &Layouts[i];

            Descriptors.push_back(NULL);
            VkDescriptorSetLayout Layout;

            if(vkAllocateDescriptorSets(*pDev, &AllocInfo, &Descriptors[i]) != VK_SUCCESS)
            {
                throw std::runtime_error("Failed to create Descriptors");
            }
        }

        VkPipelineLayoutCreateInfo LayoutInfo{};
        LayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        LayoutInfo.setLayoutCount = Layouts.size();
        LayoutInfo.pSetLayouts = Layouts.data();

        if(vkCreatePipelineLayout(*pDev, &LayoutInfo, nullptr, &PipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create pipeline layout");
        }

    // PIPELINE/SHADERS LAYOUT

    // PIPELINE/SHADERS STAGES
        ShaderStages.resize(Shaders.size());

        for(uint32_t i = 0; i < Shaders.size(); i++)
        {
            ShaderStages[i].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;

            switch (Shaders[i].Type)
            {
                case Ek::eShaderVert:
                    ShaderStages[i].stage = VK_SHADER_STAGE_VERTEX_BIT;
                    break;
                case Ek::eShaderFrag:
                    ShaderStages[i].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
                    break;
                case Ek::eShaderGeometry:
                    ShaderStages[i].stage = VK_SHADER_STAGE_GEOMETRY_BIT;
                    break;
                case Ek::eShaderCompute:
                    ShaderStages[i].stage = VK_SHADER_STAGE_COMPUTE_BIT;
                    break;
                case Ek::eShaderTesselation:
                    ShaderStages[i].stage = VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
                    break;
                default:
                    throw std::runtime_error("Failed to Resolve Shader Stage");
            }

            ShaderStages[i].pName = Shaders[i].ShaderEntryPoint;
            ShaderStages[i].module = Shaders[i].ShaderModule;

            ShaderStages[i].pNext = nullptr;
            ShaderStages[i].pSpecializationInfo = nullptr;
            ShaderStages[i].flags = 0;
        }

        VertexInput.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        VertexInput.flags = 0;
        VertexInput.pNext = nullptr;

        if(VertexClass)
        {
            // Explains how vertices look in memory
            std::vector<VkVertexInputAttributeDescription> Attribs = VertexClass->GetAttributeDescription();

            // Explains how vertices bind to vertex shaders
            std::vector<VkVertexInputBindingDescription> Bindings = VertexClass->GetBindingDescription();

            VertexInput.vertexAttributeDescriptionCount = Attribs.size();
            VertexInput.pVertexAttributeDescriptions = Attribs.data();
            VertexInput.vertexBindingDescriptionCount = Bindings.size();
            VertexInput.pVertexBindingDescriptions = Bindings.data();
        }
        else
        {
            VertexInput.vertexAttributeDescriptionCount = 0;
            VertexInput.pVertexAttributeDescriptions = nullptr;
            VertexInput.vertexBindingDescriptionCount = 0;
            VertexInput.pVertexBindingDescriptions = nullptr;
        }

    // PIPELINE/SHADERS STAGES
}

Ek::Material::~Material()
{

}

Ek::Shader::Shader(VkDevice* Device)
{
    pDev = Device;
}
