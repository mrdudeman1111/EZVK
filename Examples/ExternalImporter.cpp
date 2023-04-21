#define GLFWAPP
#include <Base/Device.h>

#include <cstring>
#include <unistd.h>

#include <vulkan/vulkan_core.h>
#include <vulkan/vk_enum_string_helper.h>

class Importer
{
    public:
    void main(int FileDescriptor);
    void SetupRenderer();

    Ek::Pipeline Pipe;
    Ek::Window* Window;
    AllocatedImage ImportedImage;
    Ek::Instance Instance;
    Ek::PhysicalDevice PDevice;
    Ek::Device Device;
    Ek::Queues Queues;
};

class Exporter
{
    public:
    int main();
    Ek::Instance EkInstance;
    Ek::PhysicalDevice PDev;
    Ek::Device Device;
    int ExportedHandle;
};

void Importer::main(int FileDescriptor)
{
    Instance.RequestInstanceExtension("VK_KHR_external_memory_capabilities");
    Instance.RequestLayer("VK_LAYER_KHRONOS_validation");
    Instance.CreateInstance(VK_API_VERSION_1_3, "Importer");

    PDevice.PickPhysDev(&Instance);
    Device = PDevice.GetLogicalDevice();

    Device.RequestExtension("VK_KHR_external_memory");
    Device.RequestExtension("VK_KHR_external_memory_fd");

    QueueList Desired{};
    Desired[QueueType::Graphics] = 1;

    Device.Create(&Instance, &Desired, &Queues);

    VkMemoryFdPropertiesKHR MemProps{};
    MemProps.sType = VK_STRUCTURE_TYPE_MEMORY_FD_PROPERTIES_KHR;

    PFN_vkGetMemoryFdPropertiesKHR GetFdProps = (PFN_vkGetMemoryFdPropertiesKHR)vkGetInstanceProcAddr(Instance.VkInst, "vkGetMemoryFdPropertiesKHR");
    GetFdProps(Device.VkDev, VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT, FileDescriptor, &MemProps);

    VkExternalMemoryImageCreateInfo ExtImgInfo{};
    ExtImgInfo.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO;
    ExtImgInfo.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;

    VkExtent3D Extent;
    Extent.width = 1920;
    Extent.height = 1080;
    Extent.depth = 1;

    VkImageCreateInfo ImageCI{};
    ImageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ImageCI.pNext = &ExtImgInfo;
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

    VkDeviceMemory ImageMemory;

    if(vkCreateImage(Device.VkDev, &ImageCI, nullptr, &ImportedImage.Image) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to Import Image");
    }

    VkMemoryRequirements MemReqs;

    vkGetImageMemoryRequirements(Device.VkDev, ImportedImage.Image, &MemReqs);

    VkImportMemoryFdInfoKHR ImportInfo;
    ImportInfo.sType = VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR;
    ImportInfo.fd = FileDescriptor;
    ImportInfo.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;

    VkMemoryAllocateInfo AllocInfo{};
    AllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocInfo.pNext = &ImportInfo;
    // if VK_MEMORY_PROPERTY_HOST_VISIBLE isn't available get VK_MEMORY_PROPERTY_HOST_COHERENT
    AllocInfo.memoryTypeIndex = PDevice.GetMemType( (MemProps.memoryTypeBits & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) ?  VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT : VK_MEMORY_PROPERTY_HOST_COHERENT_BIT );
    AllocInfo.allocationSize = MemReqs.size;

    if(vkAllocateMemory(Device.VkDev, &AllocInfo, nullptr, &ImageMemory) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to allocate memory");
    }

    vkBindImageMemory(Device.VkDev, ImportedImage.Image, ImageMemory, 0);

    // Allocation Requirements can be found in MemProps.memoryTypeBits
    return;
}

int Exporter::main()
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

    VkImage Image;

    VkExternalMemoryImageCreateInfoKHR ExtImageCI{};
    ExtImageCI.sType = VK_STRUCTURE_TYPE_EXTERNAL_MEMORY_IMAGE_CREATE_INFO_KHR;
    ExtImageCI.handleTypes = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;

    VkImageCreateInfo ImageCI{};
    ImageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    ImageCI.pNext = &ExtImageCI;
    ImageCI.format = VK_FORMAT_R8G8B8A8_SRGB;
    ImageCI.samples = VK_SAMPLE_COUNT_1_BIT;
    ImageCI.usage = VK_IMAGE_USAGE_SAMPLED_BIT;
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
    AllocInfo.memoryTypeIndex = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;

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

    vkMapMemory(Device.VkDev, ImageMemory, 0, (Width*Height*4), 0, &ImgData);
      memcpy(ImgData, Pixels, Width * Height * 4);
    vkUnmapMemory(Device.VkDev, ImageMemory);

    std::cout << "Raised Image to " << FileDescriptor << '\n';

    return FileDescriptor;
}

void Importer::SetupRenderer()
{
    Ek::Renderpass RP = Device.CreateRenderpass();
    Window = Device.CreateWindow(&Queues.GraphicsQueues[0]);
    Window->CreateWindow(1920, 1080, "VkRender");
    Window->CreateSurface();
    Window->CreateSwapchain(2);

    ImportedImage.CreateImageView(VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT);
    ImportedImage.CreateRenderTarget(VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE, VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

    std::vector<AllocatedImage*> Attachments = {&ImportedImage};

    RP.BuildSubpass(Attachments);
    Pipe = RP.CreatePipeline(1920, 1080);


    Ek::Shader Frag = Device.CreateShader(SHADERDIR"ImgFrag.glsl.spv");
    
    Ek::Shader Vert = Device.CreateShader(SHADERDIR"ImgVert.glsl.spv");

}

class OurVertex : Ek::BasicVertex
{
    public:
    glm::vec3 Position;
    glm::vec2 TexCoord;

    virtual std::vector<VkVertexInputBindingDescription> GetBindingDescription()
    {
        // Only one vertex per struct
        std::vector<VkVertexInputBindingDescription> Ret(1);
        Ret[0].binding = 0;
        Ret[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        Ret[0].stride = sizeof(OurVertex);

        return Ret;
    }

    virtual std::vector<VkVertexInputAttributeDescription> GetAttributeDescription()
    {
      std::vector<VkVertexInputAttributeDescription> Ret(2);
      Ret[0].binding = 0;
      Ret[0].format = VK_FORMAT_R32G32B32_SFLOAT;
      Ret[0].offset = offsetof(OurVertex, Position);

      Ret[1].binding = 0;
      Ret[1].format = VK_FORMAT_R32G32_SFLOAT;
      Ret[1].offset = offsetof(OurVertex, TexCoord);

      return Ret;
    }
};

int main()
{
    Importer* In = new Importer();
    Exporter* Out = new Exporter();

    int Fd = Out->main();
    In->main(Fd);

    std::cout << "Everything ran successfully, closing the file descriptor now\n";
    close(Fd);
}
