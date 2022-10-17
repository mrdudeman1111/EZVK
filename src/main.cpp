#include <EkHelpers.hpp>

int main()
{
    EkVulkan VulkanInterface;
    VulkanInterface.CreateWindow(1280, 720, "VulkanInterface");
    VulkanInterface.RequestLayer("VK_LAYER_KHRONOS_validation");
    VulkanInterface.RequestInstanceExtension("VK_EXT_debug_utils");
    VulkanInterface.CreateInstance();
    VulkanInterface.PickPhysDev();
    std::vector<std::string> RequestedQueues = { "graphics", "compute" };
    VulkanInterface.CreateDevice(&RequestedQueues);
    VulkanInterface.Window.QueryFormats(VK_FORMAT_R32G32B32_SFLOAT);
    // VulkanInterface.CreateSwapChain(VK_FORMAT_R32G32B32_SFLOAT);

    EkCmdPool* GraphicsPool = VulkanInterface.CreateCommandPool("graphics");
    GraphicsPool->AllocateCmdBuffer(0, CommandBufferUsage::OneTime);

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
