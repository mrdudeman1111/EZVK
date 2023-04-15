#include <fstream>
#include <Base/Device.h>
#include <vulkan/vulkan_core.h>

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

    VkExternalMemoryImageCreateInfoKHR ExtImgInf{};
    ExtImgInf.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_KHR;
    ExtImgInf.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;

    VkExtent3D Extent{};
    Extent.width = 1920;
    Extent.height = 1080;
    Extent.depth = 1.f;

    VkImageFormatProperties2 FrmProps{};

    VkPhysicalDeviceImageFormatInfo2 FrmInfo{};
    FrmInfo.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
    FrmInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    FrmInfo.format = VK_FORMAT_R8G8B8_UINT;

    vkGetPhysicalDeviceImageFormatProperties2(PDev.VkPhysDev, &FrmInfo, &FrmProps);
    
    VkImageCreateInfo ImgCI{};
    ImgCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ImgCI.pNext = &ExtImgInf;
    ImgCI.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
    ImgCI.extent = Extent;
    ImgCI.tiling = VK_IMAGE_TILING_OPTIMAL;
    ImgCI.pNext = &ExtImgInf;
    ImgCI.format = VK_FORMAT_B8G8R8_UINT;
    ImgCI.samples = VK_SAMPLE_COUNT_1_BIT;
    ImgCI.imageType = VK_IMAGE_TYPE_3D;
    ImgCI.mipLevels = 1;
    ImgCI.arrayLayers = 1;
    ImgCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ImgCI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    VkImage Image;
    VkDeviceMemory ImageMemory;

    if(vkCreateImage(Device.VkDev, &ImgCI, nullptr, &Image) != VK_SUCCESS)
    {
      throw std::runtime_error("Failed to create image");
    }

    VkMemoryRequirements ImageRequirements;
    vkGetImageMemoryRequirements(Device.VkDev, Image, &ImageRequirements);

    VkPhysicalDeviceMemoryProperties MemProps;
    vkGetPhysicalDeviceMemoryProperties(PDev.VkPhysDev, &MemProps);

    int MemIndex;

    for(uint32_t i = 0; i < MemProps.memoryTypeCount; i++)
    {
      if(MemProps.memoryTypes[i].propertyFlags & ImageRequirements.memoryTypeBits)
      {
        MemIndex = i;
        break;
      }
    }

    VkMemoryAllocateInfo AllocInfo;
    AllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocInfo.allocationSize = ImageRequirements.size;
    AllocInfo.memoryTypeIndex = MemIndex;

    if(vkAllocateMemory(Device.VkDev, &AllocInfo, nullptr, &ImageMemory) != VK_SUCCESS)
    {
      throw std::runtime_error("Failed to create Allocate Memory");
    }

    vkBindImageMemory(Device.VkDev, Image, ImageMemory, 0);

    VkMemoryGetFdInfoKHR GetInf{};
    GetInf.sType = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR;
    GetInf.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;
    GetInf.memory = ImageMemory;

    int ImageFd;

    PFN_vkGetMemoryFdKHR GetFd = (PFN_vkGetMemoryFdKHR)vkGetInstanceProcAddr(EkInstance.VkInst, "vkGetMemoryFdKHR");
    GetFd(Device.VkDev, &GetInf, &ImageFd);

    std::cout << "successfully raised Image Memory to file handle " << ImageFd << " on Posix\n";

    //vkGetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR *pMemoryFdProperties)

    // while(!glfwWindowShouldClose(Window->glfwWindow))
    // {
    //     glfwPollEvents();
    //     FrameBuffer* FB = Window->GetNextFrame();

    // }

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
