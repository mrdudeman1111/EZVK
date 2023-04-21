#include <Base/Device.h>
#include <vulkan/vulkan_core.h>
#include <vulkan/vk_enum_string_helper.h>

#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <map>

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
        $
        VkSubpassDescription
        VkFrameBuffer
        VkRenderPass
*/

Ek::Instance EkInstance;
Ek::PhysicalDevice PDev;
Ek::Device Device;

std::ofstream OutFile;

struct ImageConfig
{
public:
    VkFormat Format;
    VkImageTiling Tiling;
    VkImageType Type;
    VkImageUsageFlagBits UsageFlags;
};

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

    VkPhysicalDeviceExternalImageFormatInfoKHR ExtInf{};
    ExtInf.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_EXTERNAL_IMAGE_FORMAT_INFO_KHR;
    ExtInf.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;

    VkExternalMemoryImageCreateInfoKHR ExtImgInf{};
    ExtImgInf.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_KHR;
    ExtImgInf.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;

    VkExtent3D Extent{};
    Extent.width = 1920;
    Extent.height = 1080;
    Extent.depth = 1.f;

    VkImage Image;

    VkExternalMemoryImageCreateInfoKHR ExtImageCI{};
    ExtImageCI.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_KHR;
    ExtImageCI.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;

    VkImageCreateInfo ImageCI{};
    ImageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ImageCI.pNext = &ExtImageCI;
    ImageCI.format = VK_FORMAT_R8G8B8A8_SRGB;
    ImageCI.samples = VK_SAMPLE_COUNT_1_BIT;
    ImageCI.usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    ImageCI.extent = Extent;
    ImageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
    ImageCI.imageType = VK_IMAGE_TYPE_2D;
    ImageCI.mipLevels = 1;
    ImageCI.arrayLayers = 1;
    ImageCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    ImageCI.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

    if (vkCreateImage(Device.VkDev, &ImageCI, nullptr, &Image) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create Image");
    }

    VkMemoryRequirements MemReqs;
    vkGetImageMemoryRequirements(Device.VkDev, Image, &MemReqs);

    VkDeviceMemory ImageMemory;

    VkExportMemoryAllocateInfo ExportAllocInfo{};
    ExportAllocInfo.sType = VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
    ExportAllocInfo.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;

    VkMemoryDedicatedAllocateInfo DedicatedAllocInfo{};
    DedicatedAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
    DedicatedAllocInfo.pNext = &ExportAllocInfo;
    DedicatedAllocInfo.image = Image;

    VkMemoryAllocateInfo AllocInfo{};
    AllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocInfo.pNext = &DedicatedAllocInfo;
    AllocInfo.allocationSize = MemReqs.size;
    AllocInfo.memoryTypeIndex = PDev.GetMemType(MemReqs.memoryTypeBits) | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;

    if (vkAllocateMemory(Device.VkDev, &AllocInfo, nullptr, &ImageMemory) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate Memory");
    }

    if (vkBindImageMemory(Device.VkDev, Image, ImageMemory, 0) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to bind Image Memory");
    }

    int FileDescriptor;

    VkMemoryGetFdInfoKHR GetInfo{};
    GetInfo.sType = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR;
    GetInfo.memory = ImageMemory;
    GetInfo.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;

    PFN_vkGetMemoryFdKHR GetFd = (PFN_vkGetMemoryFdKHR)vkGetInstanceProcAddr(EkInstance.VkInst, "vkGetMemoryFdKHR");
    if(GetFd(Device.VkDev, &GetInfo, &FileDescriptor) != VK_SUCCESS)
    {
        throw std::runtime_error("failed to get memoryfd");
    }

    int Height, Width, Channels;
    stbi_uc *Pixels = stbi_load("/home/ethanw/Repos/VulkanWrapper/Image.jpg", &Width, &Height, &Channels, STBI_rgb_alpha);

    void *ImgData;

    vkMapMemory(Device.VkDev, ImageMemory, 0, MemReqs.size, 0, &ImgData);
    memcpy(ImgData, Pixels, Width * Height * 4);
    vkUnmapMemory(Device.VkDev, ImageMemory);

    std::cout << "Raised Image to " << FileDescriptor << '\n';

    std::string Message;

    while(strcmp(Message.c_str(), "exit"))
    {
        std::cin >> Message;
    }

    std::cout << "successful run complete\n";
    return 0;
}
