#include <EkHelpers.hpp>
#include <fstream>

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


int main()
{
    EkVulkan VulkanInterface;

    EkWindow* Window = VulkanInterface.CreateWindow(1280, 720, "VulkanInterface");

    VulkanInterface.RequestLayer("VK_LAYER_KHRONOS_validation");
    VulkanInterface.RequestInstanceExtension("VK_EXT_debug_utils");
    VulkanInterface.CreateInstance();

    VulkanInterface.PickPhysDev();

    VulkanInterface.RequestDeviceExtension("VK_KHR_swapchain");
    std::vector<std::string> RequestedQueues = { "graphics", "compute" };
    VulkanInterface.CreateDevice(&RequestedQueues);

    VulkanInterface.InitVMA();

    VulkanInterface.CreateSwapChain(VK_PRESENT_MODE_MAILBOX_KHR, 2);
    VkExtent2D Extent = Window->GetWindowExtent();

    Ek::Subpass MainPass = Window->GetFrameBufferPass(0);

    Ek::Renderpass Renderpass{};
    Renderpass.Subpasses = &MainPass;
    Renderpass.Build();

    EkCmdPool* GraphicsPool = VulkanInterface.CreateCommandPool("graphics");
    EkCommandBuffer RenderCmdBuffer = GraphicsPool->AllocateCmdBuffer(0, CommandBufferUsage::OneTime);

    #ifdef GLFWAPP
        while(!glfwWindowShouldClose(Window->Window))
        {
            glfwPollEvents();
        }
    #endif

    VulkanInterface.DeletionQueue.Run();

    std::cout << "Finished" << std::endl;
    return 0;
}
