#include <EkHelpers.hpp>

/*
    Initiate base vulkan structures (Instance, Physical Device, Device)
    Initiate Swapchain
    Initiate CommandPool/CommandBuffers
    Initiate RenderPass
    Initiate frame buffers
*/

int main()
{
    EkVulkan VulkanInterface;
    VulkanInterface.CreateWindow(1280, 720, "VulkanInterface");
    VulkanInterface.RequestLayer("VK_LAYER_KHRONOS_validation");
    VulkanInterface.RequestInstanceExtension("VK_EXT_debug_utils");
    VulkanInterface.CreateInstance();
    VulkanInterface.PickPhysDev();
    VulkanInterface.InitVMA();
    std::vector<std::string> RequestedQueues = { "graphics", "compute" };
    VulkanInterface.CreateDevice(&RequestedQueues);
    EkCmdPool* GraphicsPool = VulkanInterface.CreateCommandPool("graphics");
    EkCommandBuffer RenderCmdBuffer = GraphicsPool->AllocateCmdBuffer(0, CommandBufferUsage::OneTime);


    #ifdef GLFWAPP
        while(!glfwWindowShouldClose(VulkanInterface.Window.Window))
        {
            glfwPollEvents();
        }
    #endif

    VulkanInterface.DeletionQueue.Run();

    std::cout << "Finished" << std::endl;
    return 0;
}
