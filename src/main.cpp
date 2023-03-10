#include <fstream>
#include <cstring>
#include <Base/Device.h>

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
    EkInstance.RequestInstanceExtension("VK_KHR_external_memory_capabilites");
    EkInstance.CreateInstance();

    PDev.PickPhysDev(&EkInstance);
    Device = PDev.GetDevice();

    Device.RequestExtension("VK_KHR_external_memory");
    Device.RequestExtension("VK_KHR_external_memory_fd");

    QueueList DesiredQueues{};
    DesiredQueues.emplace(Graphics, 1);
    Device.Create(&EkInstance, &PDev, DesiredQueues, &Queues);

    Ek::CmdPool* CmdPool = Device.CreateCommandPool(QueueType::Graphics);
    CmdPool->AllocateCmdBuffer(0, CommandBufferUsage::RenderPass);

    Ek::Window* Window = Device.CreateWindow(&Queues.GraphicsQueues[0]);

    Window->CreateWindow(1280, 720, "Tester");
    Window->CreateSurface();

    Ek::Renderpass Renderpass = Device.CreateRenderpass();
    Renderpass.BuildSubpass()

    Window->CreateSwapchain(3);

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
