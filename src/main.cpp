#include <Base/Device.h>
#include <vulkan/vulkan_core.h>
#include <cstring>

/*
    Ideas:
        Shader layout builder
*/

/*
    Images explained:
        It starts with an AllocatedImage/FrameBuffer. This base class will create a VkImage and then a VkImageView. After that it will proceed to create an AttDesc if requested ( CreateRenderTarget ).
        After that, you pass it to a renderpass and it will handle creating VkAttachmentRerence s
*/

/*
    Creation order
        VkImage
        VkImageView
        VkAttachmentDescription
        VkAttachmentReference
        VkSubpassDescription
        VkFrameBuffer
        VkRenderPass
*/

Ek::Instance EkInstance;
Ek::PhysicalDevice PDev;
Ek::Device Device;
Ek::Queues Queues;

int main()
{
    EkInstance.RequestInstanceExtension("VK_KHR_external_memory_capabilities");
    EkInstance.RequestLayer("VK_LAYER_KHRONOS_validation");
    EkInstance.CreateInstance(VK_API_VERSION_1_3, "external texture Tester");

    PDev.PickPhysDev(&EkInstance);
    Device = PDev.GetLogicalDevice();

    Device.RequestExtension("VK_KHR_external_memory");
    Device.RequestExtension("VK_KHR_external_memory_fd");
    Device.Create(&EkInstance, nullptr, nullptr);

    GLFWwindow* Window = glfwCreateWindow(1280, 720, "Stud", NULL, NULL);

    std::vector<uint32_t> AvailableFormats;

    for(uint32_t i = 0; i < 184; i++)
    {
        VkPhysicalDeviceExternalImageFormatInfoKHR ExtImgInfo{};
        ExtImgInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO_KHR;
        ExtImgInfo.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT_KHR;

        VkPhysicalDeviceImageFormatInfo2 ImgInfo{};
        ImgInfo.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_IMAGE_FORMAT_INFO_2;
        ImgInfo.pNext = &ExtImgInfo;
        ImgInfo.format = VkFormat(i);
        ImgInfo.tiling = VK_IMAGE_TILING_LINEAR;
        ImgInfo.type = VK_IMAGE_TYPE_3D;
        ImgInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT;

        VkExternalImageFormatProperties ExtFrmProps{};
        ExtFrmProps.sType = VK_STRUCTURE_TYPE_EXTERNAL_IMAGE_FORMAT_PROPERTIES;

        VkImageFormatProperties2 FrmProps{};
        FrmProps.sType = VK_STRUCTURE_TYPE_IMAGE_FORMAT_PROPERTIES_2;
        FrmProps.pNext = &ExtFrmProps;

        if(vkGetPhysicalDeviceImageFormatProperties2(PDev.VkPhysDev, &ImgInfo, &FrmProps) == VK_SUCCESS)
        {
            AvailableFormats.push_back(i);
        }
    }

    std::cout << "Available Formats Include\n";

    for(uint32_t Num : AvailableFormats)
    {
        printf("%d\n", Num);
    }

    VkPhysicalDeviceExternalImageFormatInfoKHR ExtInf{};
    ExtInf.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO_KHR;
    ExtInf.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT_KHR;

    VkExternalMemoryImageCreateInfoKHR ExtImgInf{};
    ExtImgInf.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_KHR;
    ExtImgInf.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT_KHR;

    VkExtent3D Extent{};
    Extent.width = 1920;
    Extent.height = 1080;
    Extent.depth = 1.f;

    VkImage Image;

    VkExternalMemoryImageCreateInfoKHR ExtImageCI{};
    ExtImageCI.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_KHR;
    ExtImageCI.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT_KHR;

    VkImageCreateInfo ImageCI{};
    ImageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ImageCI.pNext = &ExtImageCI;
    ImageCI.format = VK_FORMAT_R8G8B8A8_SRGB;
    ImageCI.samples = VK_SAMPLE_COUNT_1_BIT;
    ImageCI.usage = VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
    ImageCI.extent = Extent;
    ImageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
    ImageCI.imageType = VK_IMAGE_TYPE_3D;
    ImageCI.mipLevels = 1;
    ImageCI.arrayLayers = 1;
    ImageCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ImageCI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    if(vkCreateImage(Device.VkDev, &ImageCI, nullptr, &Image) != VK_SUCCESS)
    {
      throw std::runtime_error("Failed to create Image");
    }

    VkMemoryRequirements MemReqs;
    vkGetImageMemoryRequirements(Device.VkDev, Image, &MemReqs);

    VkDeviceMemory ImageMemory;

    VkExportMemoryAllocateInfo ExportAllocInfo{};
    ExportAllocInfo.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
    ExportAllocInfo.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT_KHR;

    VkMemoryAllocateInfo AllocInfo{};
    AllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocInfo.pNext = &ExportAllocInfo;
    AllocInfo.allocationSize = MemReqs.size;
    AllocInfo.memoryTypeIndex = PDev.GetMemType(MemReqs.memoryTypeBits);

    if(vkAllocateMemory(Device.VkDev, &AllocInfo, nullptr, &ImageMemory) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate Image memory");
    }

    if(vkBindImageMemory(Device.VkDev, Image, ImageMemory, 0) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to bind Image memory");
    }

    int FileDescriptor;

    VkMemoryGetFdInfoKHR GetInfo{};
    GetInfo.sType = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR;
    GetInfo.memory = ImageMemory;
    GetInfo.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT_KHR;

    PFN_vkGetMemoryFdKHR GetFd = (PFN_vkGetMemoryFdKHR)vkGetInstanceProcAddr(EkInstance.VkInst, "vkGetMemoryFdKHR");
    GetFd(Device.VkDev, &GetInfo, &FileDescriptor);

    int Height, Width, Channels;
    stbi_uc* Pixels = stbi_load("/home/ethanw/Repos/VulkanWrapper/Image.jpg", &Width, &Height, &Channels, STBI_rgb_alpha);

    void* ImgData;

    vkMapMemory(Device.VkDev, ImageMemory, 0, MemReqs.size, 0, &ImgData);
        memcpy(ImgData, Pixels, Width * Height * 4);
    vkUnmapMemory(Device.VkDev, ImageMemory);

    std::cout << "Raised Image to " << FileDescriptor << '\n';

    std::string Message;

    while(strcmp(Message.c_str(), "stop") || glfwWindowShouldClose(Window))
    {
        std::cin >> Message;
    }

    glfwDestroyWindow(Window);
    glfwTerminate();

    std::cout << "successful run complete\n";
    return 0;
}


// int main()
// {
//     EkVulkan VulkanInterface;

//     EkWindow* Window = VulkanInterface.CreateWindow(1280, 720, "VulkanInterface");

//     VulkanInterface.RequestLayer("VK_LAYER_KHRONOS_validation");
//     VulkanInterface.RequestInstanceExtension("VK_EXT_debug_utils");
//     VulkanInterface.CreateInstance();

//     VulkanInterface.PickPhysDev();

//     VulkanInterface.RequestDeviceExtension("VK_KHR_swapchain");
//     std::vector<std::string> RequestedQueues = { "graphics", "compute" };
//     VulkanInterface.CreateDevice(&RequestedQueues);

//     VulkanInterface.InitVMA();

//     // Second argument adds # additional frame buffers to the swapchain
//     Window->CreateSwapchain(3, VK_PRESENT_MODE_MAILBOX_KHR, 0);
//     VkExtent2D Extent = Window->GetWindowExtent();
//     VkRect2D RenderArea;
//     RenderArea.offset = VkOffset2D{0, 0};
//     RenderArea.extent = Extent;

//     // Setup Renderpasses

//         Ek::Subpass MainPass = Window->GetFrameBufferPass(0);

//         Ek::Renderpass Renderpass{};
//         Renderpass.Subpasses = &MainPass;
//         Renderpass.Build(&MainPass);

//     // Setup Commands

//         EkCmdPool* GraphicsPool = VulkanInterface.CreateCommandPool("graphics");
//         Ek::CommandBuffer Render = GraphicsPool->AllocateCmdBuffer(0, CommandBufferUsage::RenderPass);

//     // Setup Shaders

//         Shaders::EkShader Vert;

//         std::string VPath = ShaderPath;
//         VPath.append("Vert.glsl.spv");
//         Vert.ShaderModule = Shaders::CreateShaderModule(VPath);
//         // This Name is passed to a VkShaderStateCreateInfo.pName which is the name of the entrypoint function
//         Vert.ShaderEntryPointName = "main";
//         Vert.Stage = VK_SHADER_STAGE_VERTEX_BIT;

//         Shaders::EkShader Frag;

//         std::string FPath = ShaderPath;
//         FPath.append("Frag.glsl.spv");
//         Frag.ShaderModule = Shaders::CreateShaderModule(FPath);
//         // This Name is passed to a VkShaderStateCreateInfo.pName which is the name of the entrypoint function
//         Frag.ShaderEntryPointName = "main";
//         Frag.Stage = VK_SHADER_STAGE_FRAGMENT_BIT;

//     // Setup main pipeline
//         Ek::Pipeline MainPipeline;
//         MainPipeline.Renderpass = &Renderpass;
//         MainPipeline.VT = VertexType::VTX_Basic;
//         MainPipeline.Shaders.push_back(&Vert);
//         MainPipeline.Shaders.push_back(&Frag);
//         MainPipeline.CreateGraphicsPipeline(Extent.height, Extent.width);

//         std::vector<VkClearValue> ClearValues = { {{ 0.1f, 0.1f, 0.1f, 1.0f }}, {{ 0.0f, 0.0f, 0.0f, 1.f }} };

//         Render.Begin();
//             Renderpass.Begin(&Render, &Window->FrameBuffers[0].FB, &RenderArea, &ClearValues);
//                 vkCmdBindPipeline(Render.CmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, MainPipeline.Pipeline);
//                 vkCmdDrawIndexed(Render.CmdBuffer, 0, 0, 0, 0, 0);
//             Renderpass.End(&Render);
//         Render.End();

//     #ifdef GLFWAPP
//         while(!glfwWindowShouldClose(Window->Window))
//         {
//             glfwPollEvents();
//         }
//     #endif

//     VulkanInterface.DeletionQueue.Run();

//     std::cout << "Finished" << std::endl;
//     return 0;
// }
