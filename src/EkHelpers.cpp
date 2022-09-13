#include <EkHelpers.hpp>
#include <VkBootstrap.h>

// Vulkan Basics
    VkInstance Instance;
    VkPhysicalDevice PhysDev;
    VkDevice Device;
    std::vector<const char*> Layers;
    std::vector<const char*> Extensions;
    const char** GlfwExts;

// Vma stuff
    VmaAllocator Allocator;

// Vulkan Queues
    VkQueue GraphicsQueue;
    VkQueue PresentQueue;
    int GraphicsQueueFamilyIndex;

// Window Stuff
    GLFWwindow* Window;
    int Width = 1280;
    int Height = 720;
    VkSurfaceKHR Surface;

void ThrowError(const char* Error)
{
    throw std::runtime_error(Error);
}

namespace Buffers
{
    void CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, AllocatedBuffer* AllocatedBuffer, VmaMemoryUsage MemUse)
    {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = Size;
        bufferInfo.usage = Usage;

        VmaAllocationCreateInfo VmaAllocateCreateInfo = {};
        VmaAllocateCreateInfo.usage = MemUse;

        if(auto res = vmaCreateBuffer(Allocator, &bufferInfo, &VmaAllocateCreateInfo, &AllocatedBuffer->Buffer, &AllocatedBuffer->Allocation, nullptr) != VK_SUCCESS)
        {
            std::cerr << "Error: " << res << std::endl; 
            throw std::runtime_error("Failed to create a buffer");
        }
    }
}

namespace Mesh
{
    // glm::mat4 ConvertMat4(aiMatrix4x4 AssimpMatrix)
    // {
    //     glm::mat4 Result
    //     (
    //         AssimpMatrix[0][0], AssimpMatrix[3][1], AssimpMatrix[3][2], AssimpMatrix[0][3],
    //         AssimpMatrix[1][0], AssimpMatrix[2][1], AssimpMatrix[2][2], AssimpMatrix[1][3],
    //         AssimpMatrix[2][0], AssimpMatrix[1][1], AssimpMatrix[1][2], AssimpMatrix[2][3],
    //         AssimpMatrix[3][0], AssimpMatrix[0][1], AssimpMatrix[0][2], AssimpMatrix[3][3]
    //     );
    //     return Result;
    // }
}

namespace InitHelpers
{
    bool CheckDevice(VkPhysicalDevice* Device)
    {
        VkPhysicalDeviceProperties DeviceProperties;
        vkGetPhysicalDeviceProperties(*Device, &DeviceProperties);

        VkPhysicalDeviceFeatures DeviceFeatures;
        vkGetPhysicalDeviceFeatures(*Device, &DeviceFeatures);

        std::cout << DeviceProperties.apiVersion;
    }

    void InitGlfw()
    {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        Window = glfwCreateWindow(Width, Height, "Vulkan Renderer", nullptr, nullptr);

        uint32_t glfwExtCount = 0;
        GlfwExts = glfwGetRequiredInstanceExtensions(&glfwExtCount);

        if(glfwVulkanSupported() != GLFW_TRUE)
        {
            throw std::runtime_error("vulkan is not supported for glfw");
        }
    }

    void RequestLayer(const char* LayerName)
    {
        Layers.push_back(LayerName);
    }

    void RequestExtension(const char* ExtensionName)
    {
        Extensions.push_back(ExtensionName);
    }

    void InitVMA()
    {
	    VmaAllocatorCreateInfo AllocatorInfo = {};
	    AllocatorInfo.physicalDevice = PhysDev;
	    AllocatorInfo.device = Device;
	    AllocatorInfo.instance = Instance;
	    vmaCreateAllocator(&AllocatorInfo, &Allocator);
    }

    void CreateInstance()
    {
        VkInstanceCreateInfo InstCI{};
        InstCI.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        InstCI.enabledLayerCount = Layers.size();
        InstCI.ppEnabledLayerNames = Layers.data();
        InstCI.enabledExtensionCount = Extensions.size();
        InstCI.ppEnabledExtensionNames = Extensions.data();

        if(vkCreateInstance(&InstCI, nullptr, &Instance))
        {
            ThrowError("Failed to create Instance");
        }






        // vkb::InstanceBuilder instance_builder;
        // instance_builder.request_validation_layers(true);

        // instance_builder.set_debug_callback (
        // [] (VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        //     VkDebugUtilsMessageTypeFlagsEXT messageType,
        //     const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        //     void *pUserData) 
        // -> VkBool32 {
        //                 auto severity = vkb::to_string_message_severity (messageSeverity);
        //                 auto type = vkb::to_string_message_type (messageType);
        //                 printf ("[%s: %s] %s\n", severity, type, pCallbackData->pMessage);
        //                 return VK_FALSE;
        //             }
        //     );

        // auto system_info_ret = vkb::SystemInfo::get_system_info();
        // if (!system_info_ret) 
        // {
        //         printf("%s\n", system_info_ret.error().message());
        //         throw std::runtime_error("failed to get system Info");
        // }

        // auto system_info = system_info_ret.value();

        // for(uint16_t i = 0; i < Layers.size())
        // {
        //     if(system_info.is_layer_available(Layers[i]))
        //     {
        //         instance_builder.enable_layer(Layers[i]);
        //     }
        // }

        // for(uint16_t i = 0; i < Extensions.size())
        // {
        //     if(system_info.is_extension_available(Extensions[i]))
        //     {
        //         instance_builder.enable_extension(Extensions[i]);
        //     }
        // }

        // auto instance_ret = instance_builder.require_api_version(1,2,0).build();

        // if(!instance_ret)
        // {
        //     std::cout << instance_ret.error().message() << "\n";
        // }

        // vkb::Instance vkbInst = instance_ret.value();
        // Instance = vkbInst.instance;

        // vkb::PhysicalDeviceSelector PhysDevSelector(vkbInst);
        // auto PhysDevResult = PhysDevSelector.set_surface(Surface).select();
        // if(!PhysDevResult)
        // {
        //     std::cout << "Physical Device selector failed with an error message saying: " << PhysDevResult.error().message() << "\n";
        // }
        // vkb::PhysicalDevice vkbPDev = PhysDevResult.value();
        // PhysDev = vkbPDev.physical_device;

        // vkb::DeviceBuilder DevBuilder{ vkbPDev };
        // auto DeviceResult = DevBuilder.build();
        // if(!DeviceResult)
        // {
        //     std::cout << "Device Creation failed" << DeviceResult.error().message() << std::endl;
        // }
        // vkbDevice = DeviceResult.value();
        // VkDevice Device = vkbDevice.device;
        // GraphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
        // PresentQueue = vkbDevice.get_queue(vkb::QueueType::present).value();
        // GraphicsQueueFamilyIndex = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();
    }

    void PickPhysDev()
    {
        uint32_t DeviceCount = 0;
        vkEnumeratePhysicalDevices(Instance, &DeviceCount, nullptr);

        if(DeviceCount == 0);
        {
            ThrowError("Failed to find a gpu with vulkan support");
        }

        std::vector<VkPhysicalDevice> Devices(DeviceCount);
        vkEnumeratePhysicalDevices(Instance, &DeviceCount, Devices.data());

        for (auto Device : Devices) 
        {
            if (CheckDevice(&Device)) 
            {
                PhysDev = Device;
                break;
            }
        }

        if (PhysDev == VK_NULL_HANDLE) 
        {
            ThrowError("Failed to find a gpu with vulkan support");
        }
    }

    void CreateSwapChain(VkDevice* Device, VkInstance* Instance)
    {
        // VkSwapchainCreateInfoKHR
    }
}

namespace Pipeline
{
    // std::vector<char> ReadFile(std::string& FileName)
    // {
    //     std::ifstream file(FileName, std::ios::ate | std::ios::binary);

    //     if (!file.is_open ()) 
    //     {
    //         throw std::runtime_error ("failed to open file!");
    //     }

    //     size_t file_size = (size_t)file.tellg ();
    //     std::vector<char> buffer (file_size);

    //     file.seekg (0);
    //     file.read (buffer.data (), static_cast<std::streamsize> (file_size));

    //     file.close ();

    //     return buffer;
    // }

    // VkShaderModule CreateShaderModule(std::string& FileName)
    // {
    //     std::vector<char> Code = ReadFile(FileName);
    //     VkShaderModuleCreateInfo Info = {};
    //     Info.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    //     Info.codeSize = Code.size();
    //     Info.pCode = reinterpret_cast<const uint32_t*> (Code.data());

    //     VkShaderModule ShaderModule;
    //     auto Res = vkCreateShaderModule(GlobalConstants::Device, &Info, nullptr, &ShaderModule);
    //     if(Res != VK_SUCCESS)
    //     {
    //         std::cout << "Error: " << Res << std::endl;
    //         throw std::runtime_error("Failed to create a shadermodule");
    //     }
    //     return ShaderModule;
    // }

    // // When messing with descriptors you do have to mess with the pipelinelayout in CreateGraphicsPipeline
    // // void CreateGraphicsPipeline()
    // // {
    // //     auto vertShaderCode = ReadFile(PipelineInfo->VertShaderPath);
    // //     auto fragShaderCode = ReadFile(PipelineInfo->FragShaderPath);

    // //     VkShaderModule VertShaderModule = CreateShaderModule(vertShaderCode, GlobalConstants::Device);
    // //     VkShaderModule FragShaderModule = CreateShaderModule(fragShaderCode, GlobalConstants::Device);

    // //     VkPipelineShaderStageCreateInfo VertShaderStage{};
    // //     VertShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    // //     VertShaderStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
    // //     VertShaderStage.module = VertShaderModule;
    // //     VertShaderStage.pName = "main";

    // //     VkPipelineShaderStageCreateInfo FragShaderStage{};
    // //     FragShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    // //     FragShaderStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    // //     FragShaderStage.module = FragShaderModule;
    // //     FragShaderStage.pName = "main";

    // //     VkPipelineShaderStageCreateInfo ShaderStages[2];
    // //     ShaderStages[0] = VertShaderStage;
    // //     ShaderStages[1] = FragShaderStage;

    // //     VkPipelineVertexInputStateCreateInfo VertInputInfo{};
    // //     VertInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    // //     std::vector<VkVertexInputBindingDescription> BindingDescription(1);
    // //     BindingDescription = RiggedVertex::GetBindingDescription();
    // //     std::vector<VkVertexInputAttributeDescription> AttributeDescription(5);
    // //     AttributeDescription = RiggedVertex::GetAttributeDescription();

    // //     VertInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(BindingDescription.size());
    // //     VertInputInfo.pVertexBindingDescriptions = BindingDescription.data();
    // //     VertInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(AttributeDescription.size());
    // //     VertInputInfo.pVertexAttributeDescriptions = AttributeDescription.data();

    // //     std::vector<VkDescriptorSetLayout> DescriptorLayouts (2);

    // //     DescriptorLayouts[0] = GlobalConstants::CameraDescriptorLayout;
    // //     DescriptorLayouts[1] = GlobalConstants::SkeletalDescriptorLayout;
        
    // //     VkPipelineLayoutCreateInfo PipelineLayoutInfo{};
    // //     PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	// //     PipelineLayoutInfo.setLayoutCount = 2;
    // //     PipelineLayoutInfo.pSetLayouts = DescriptorLayouts.data();

    // //     //Make sure it's not a problem with the shaders. And that they've been compiled
    // //     if(vkCreatePipelineLayout(GlobalConstants::Device, &PipelineLayoutInfo, nullptr, &PipelineInfo->PipelineLayout) != VK_SUCCESS) 
    // //     {
    // //         throw std::runtime_error("failed to create pipeline layout!");
    // //     }

    // //     VkPipelineInputAssemblyStateCreateInfo InputAssembly{};
    // //     InputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    // //     InputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    // //     InputAssembly.primitiveRestartEnable = VK_FALSE;

    // //     VkViewport Viewport{};
    // //     Viewport.x = 0;
    // //     Viewport.y = 0;
    // //     Viewport.width = (float) PipelineInfo->Width;
    // //     Viewport.height = (float) PipelineInfo->Height;
    // //     Viewport.minDepth = 0.0f;
    // //     Viewport.maxDepth = 1.0f;

    // //     VkRect2D Scissor{};
    // //     Scissor.offset = {0, 0};
    // //     Scissor.extent = VkExtent2D{(uint32_t) PipelineInfo->Width, (uint32_t) PipelineInfo->Height};

    // //     VkPipelineViewportStateCreateInfo ViewportState{};
    // //     ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    // //     ViewportState.viewportCount = 1;
    // //     ViewportState.pViewports = &GlobalConstants::Viewport;
    // //     ViewportState.scissorCount = 1;
    // //     ViewportState.pScissors = &Scissor;

    // //     VkPipelineRasterizationStateCreateInfo Rasterizer{};
    // //     Rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    // //     Rasterizer.depthClampEnable = VK_FALSE;
    // //     Rasterizer.rasterizerDiscardEnable = VK_FALSE;
    // //     Rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    // //     Rasterizer.lineWidth = 1.0f;
    // //     Rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    // //     Rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    // //     Rasterizer.depthBiasEnable = VK_FALSE;

    // //     VkPipelineMultisampleStateCreateInfo MultiSampling{};
    // //     MultiSampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    // //     MultiSampling.sampleShadingEnable = VK_FALSE;
    // //     MultiSampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    // //     VkPipelineColorBlendAttachmentState ColorBlendAttachment{};
    // //     ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    // //     ColorBlendAttachment.blendEnable = VK_FALSE;

    // //     VkPipelineColorBlendStateCreateInfo ColorBlendingState{};
    // //     ColorBlendingState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    // //     ColorBlendingState.logicOpEnable = VK_FALSE;
    // //     ColorBlendingState.logicOp = VK_LOGIC_OP_COPY;
    // //     ColorBlendingState.attachmentCount = 1;
    // //     ColorBlendingState.pAttachments = &ColorBlendAttachment;
    // //     ColorBlendingState.blendConstants[0] = 0.0f;
    // //     ColorBlendingState.blendConstants[1] = 0.0f;
    // //     ColorBlendingState.blendConstants[2] = 0.0f;
    // //     ColorBlendingState.blendConstants[3] = 0.0f;

    // //     //Create Depth Stencil State
    // //     VkPipelineDepthStencilStateCreateInfo DepthStencil = {};
    // //     DepthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    // //     DepthStencil.pNext = nullptr;

    // //     DepthStencil.depthTestEnable = true ? VK_TRUE : VK_FALSE;
    // //     DepthStencil.depthWriteEnable = true ? VK_TRUE : VK_FALSE;
    // //     DepthStencil.depthCompareOp = true ? VK_COMPARE_OP_LESS_OR_EQUAL : VK_COMPARE_OP_ALWAYS;
    // //     DepthStencil.depthBoundsTestEnable = VK_FALSE;
    // //     DepthStencil.minDepthBounds = 0.0f; // Optional
    // //     DepthStencil.maxDepthBounds = 1.0f; // Optional
    // //     DepthStencil.stencilTestEnable = VK_FALSE;

    // //     VkGraphicsPipelineCreateInfo PipelineCreateInfo{};
    // //     PipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    // //     PipelineCreateInfo.stageCount = 2;
    // //     PipelineCreateInfo.pStages = ShaderStages;
    // //     PipelineCreateInfo.pVertexInputState = &VertInputInfo;
    // //     PipelineCreateInfo.pInputAssemblyState = &InputAssembly;
    // //     PipelineCreateInfo.pViewportState = &ViewportState;
    // //     PipelineCreateInfo.pRasterizationState = &Rasterizer;
    // //     PipelineCreateInfo.pMultisampleState = &MultiSampling;
    // //     PipelineCreateInfo.pColorBlendState = &ColorBlendingState;
    // //     PipelineCreateInfo.layout = PipelineInfo->PipelineLayout;
    // //     PipelineCreateInfo.renderPass = PipelineInfo->RenderPass;
    // //     PipelineCreateInfo.subpass = 0;
    // //     PipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
    // //     PipelineCreateInfo.pDepthStencilState = &DepthStencil;

    // //     VkSwapchainKHR SwapChains[] = { *PipelineInfo->SwapChain };
        
	// //     //Make sure it's not a problem with the shaders. and that they've been compiled
	// // 	auto Error = vkCreateGraphicsPipelines(GlobalConstants::Device, VK_NULL_HANDLE, 1, &PipelineCreateInfo, nullptr, &PipelineInfo->GraphicsPipeline);
    // //     if(Error != VK_SUCCESS)
    // //     {
	// // 		std::cout << "Failed to create graphics pipeline! Error: " << Error << std::endl;
    // //         throw std::runtime_error("failed to create graphics pipeline!");
    // //     }

    // //     vkDestroyShaderModule(GlobalConstants::Device, FragShaderModule, nullptr);
    // //     vkDestroyShaderModule(GlobalConstants::Device, VertShaderModule, nullptr);
    // // }

    // VkWriteDescriptorSet WriteToDescriptor(VkDescriptorType type, VkDescriptorSet dstSet, VkDescriptorBufferInfo* bufferInfo , uint32_t binding)
    // {
    //     VkWriteDescriptorSet write = {};
    //     write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    //     write.pNext = nullptr;

    //     write.dstBinding = binding;
    //     write.dstSet = dstSet;
    //     write.descriptorCount = 1;
    //     write.descriptorType = type;
    //     write.pBufferInfo = bufferInfo;

    //     return write;
    // }

}
