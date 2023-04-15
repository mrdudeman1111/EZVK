#include <Images/EkImages.hpp>
#include <Base/EkTypes.hpp>

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

void Warn(const char* Error)
{
    std::cerr << Error << std::endl;
}

// Utility function. Definition found in BaseEkTypes.hpp
std::vector<char> ReadFile(const char* FileName)
{
    std::ifstream File(FileName, std::ios::ate | std::ios::binary);

    if(!File.is_open()) 
    {
        throw std::runtime_error ("failed to open file!");
    }

    size_t FileSize = File.tellg();
    std::vector<char> Buffer(FileSize);

    File.seekg(0);
    File.read(Buffer.data(), static_cast<std::streamsize>(FileSize));

    File.close();

    return Buffer;
}

// Allocated Image
    AllocatedImage::AllocatedImage(VkDevice* PDev)
    {
        Device = PDev;
    }

    void AllocatedImage::CreateImageView(VkImageViewType ViewType, VkImageAspectFlagBits Aspects)
    {
        VkImageViewCreateInfo CreateInfo{};
        CreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        CreateInfo.image = Image;
        CreateInfo.viewType = ViewType;
        CreateInfo.format = Format;
        CreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.subresourceRange.aspectMask = Aspects;
        CreateInfo.subresourceRange.baseMipLevel = 0;
        CreateInfo.subresourceRange.levelCount = 1;
        CreateInfo.subresourceRange.baseArrayLayer = 0;
        CreateInfo.subresourceRange.layerCount = 1;

        if(vkCreateImageView(*Device, &CreateInfo, nullptr, &ImageView) != VK_SUCCESS)
        {
            ThrowError("Failed to Create Image View");
        }
    }

    void AllocatedImage::CreateRenderTarget(VkAttachmentLoadOp LoadOp, VkAttachmentStoreOp StoreOp, VkAttachmentLoadOp StencilLoad, VkAttachmentStoreOp StencilStore, int EndLayout)
    {
        AttDesc Attachment;
        Attachment.Att.samples = VK_SAMPLE_COUNT_1_BIT;

        Attachment.Att.format = Format;
        Attachment.Att.samples = VK_SAMPLE_COUNT_1_BIT;
        Attachment.Att.loadOp = LoadOp;
        Attachment.Att.storeOp = StoreOp;
        Attachment.Att.stencilLoadOp = StencilLoad;
        Attachment.Att.stencilStoreOp = StencilStore;
        Attachment.Att.initialLayout = Layout;

        if(EndLayout != -1)
        {
            Attachment.Att.finalLayout = static_cast<VkImageLayout>(EndLayout);
        }
        else
        {
            Attachment.Att.finalLayout = Layout;
        }

        Attachment.Layout = Layout;
    }

// Frame Buffer
    void FrameBuffer::InitImages(AllocatedImage* SwapImage, AllocatedImage* DepthImage, VkImageViewType ViewType)
    {
        // These Images are already allocated and instantiated, they are created with the Swapchain
        ImageBuffer.CreateImageView(ViewType, VK_IMAGE_ASPECT_COLOR_BIT);
        ImageBuffer.CreateRenderTarget(VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE, VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
        ImageBuffer.Type = RtType::RtColor;

        DepthBuffer.CreateImageView(ViewType, VK_IMAGE_ASPECT_DEPTH_BIT);
        DepthBuffer.CreateRenderTarget(VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_DONT_CARE, VK_IMAGE_LAYOUT_DEPTH_ATTACHMENT_OPTIMAL);
        DepthBuffer.Type = RtType::RtDepth;
    }

    void FrameBuffer::Build(VkRenderPass* RenderPass, VkExtent3D ImageExtent)
    {
        VkFramebufferCreateInfo FBInfo;
        FBInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        FBInfo.width = ImageExtent.width;
        FBInfo.height = ImageExtent.height;

        FBInfo.attachmentCount = 2;
        VkImageView Attachments[2] = { ImageBuffer.ImageView, DepthBuffer.ImageView };

        FBInfo.pAttachments = Attachments;
        FBInfo.layers = 1;
    }

    // bool Image::AllocateImage(VkImageType ImageType, VkExtent3D Extent, VkFormat ImageFormat, VkImageLayout Layout, VmaMemoryUsage MemUse, uint32_t MipLevels, VkImageUsageFlags ImageUsage, AllocatedImage* PassedImage)
    // {
    //     PassedImage->Format = ImageFormat;
    //     PassedImage->Layout = Layout;

    //     VkImageCreateInfo ImageCI = {};
    //     ImageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    //     ImageCI.imageType = ImageType;
    //     ImageCI.format = ImageFormat;
    //     ImageCI.extent = Extent;
    //     ImageCI.mipLevels = MipLevels;
    //     ImageCI.arrayLayers = 1;
    //     ImageCI.samples = VK_SAMPLE_COUNT_1_BIT;
    //     ImageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
    //     ImageCI.usage = ImageUsage;

    //     VmaAllocationCreateInfo AllocInfo = {};
    //     AllocInfo.usage = MemUse;

    //     vmaCreateImage(*Allocator, &ImageCI, &AllocInfo, &PassedImage->Image, &PassedImage->Allocation, nullptr);

    //     return true;
    // }

    // AttDesc Image::BuildRenderTarget(VkImageLayout InitLayout, VkImageLayout FinalLayout, AllocatedImage* Image, VkAttachmentLoadOp LoadOp, VkAttachmentStoreOp StoreOp, VkAttachmentLoadOp StencilLoadOp, VkAttachmentStoreOp StencilStoreOp)
    // {
    //     AttDesc Attachment;
    //     Attachment.Att.format = Image->Format;
    //     Attachment.Att.samples = VK_SAMPLE_COUNT_1_BIT;
    //     Attachment.Att.loadOp = LoadOp;
    //     Attachment.Att.storeOp = StoreOp;
    //     Attachment.Att.stencilLoadOp = StencilLoadOp;
    //     Attachment.Att.stencilStoreOp = StencilStoreOp;
    //     Attachment.Att.initialLayout = InitLayout;
    //     Attachment.Att.finalLayout = FinalLayout;

    //     Attachment.Layout = Image->Layout;
    //     return Attachment;
    // }
