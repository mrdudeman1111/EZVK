#include <Images/EkImages.hpp>

#define VMA_IMPLEMENTATION
#include <vk_mem_alloc.h>

void Warn(const char* Error)
{
    std::cerr << Error << std::endl;
}

// Allocated Image
    void Image::AllocateImageView(VkImageViewType ViewType, VkImageAspectFlagBits Aspects, AllocatedImage* PassedImage)
    {
        VkImageViewCreateInfo CreateInfo{};
        CreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        CreateInfo.image = PassedImage->Image;
        CreateInfo.viewType = ViewType;
        CreateInfo.format = PassedImage->Format;
        CreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.subresourceRange.aspectMask = Aspects;
        CreateInfo.subresourceRange.baseMipLevel = 0;
        CreateInfo.subresourceRange.levelCount = 1;
        CreateInfo.subresourceRange.baseArrayLayer = 0;
        CreateInfo.subresourceRange.layerCount = 1;

        if(vkCreateImageView(GlobDevice, &CreateInfo, nullptr, &PassedImage->ImageView) != VK_SUCCESS)
        {
            ThrowError("Failed to Create Image View");
        }
    }

    bool Image::AllocateImage(VkImageType ImageType, VkExtent3D Extent, VkFormat ImageFormat, VkImageLayout Layout, VmaMemoryUsage MemUse, uint32_t MipLevels, VkImageUsageFlags ImageUsage, AllocatedImage* PassedImage)
    {
        PassedImage->Format = ImageFormat;
        PassedImage->Layout = Layout;

        VkImageCreateInfo ImageCI = {};
        ImageCI.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ImageCI.imageType = ImageType;
        ImageCI.format = ImageFormat;
        ImageCI.extent = Extent;
        ImageCI.mipLevels = MipLevels;
        ImageCI.arrayLayers = 1;
        ImageCI.samples = VK_SAMPLE_COUNT_1_BIT;
        ImageCI.tiling = VK_IMAGE_TILING_OPTIMAL;
        ImageCI.usage = ImageUsage;

        VmaAllocationCreateInfo AllocInfo = {};
        AllocInfo.usage = MemUse;

        vmaCreateImage(Allocator, &ImageCI, &AllocInfo, &PassedImage->Image, &PassedImage->Allocation, nullptr);

        return true;
    }

    AttDesc Image::BuildRenderTarget(VkImageLayout InitLayout, VkImageLayout FinalLayout, AllocatedImage* Image, VkAttachmentLoadOp LoadOp, VkAttachmentStoreOp StoreOp, VkAttachmentLoadOp StencilLoadOp, VkAttachmentStoreOp StencilStoreOp)
    {
        AttDesc Attachment;
        Attachment.Att.format = Image->Format;
        Attachment.Att.samples = VK_SAMPLE_COUNT_1_BIT;
        Attachment.Att.loadOp = LoadOp;
        Attachment.Att.storeOp = StoreOp;
        Attachment.Att.stencilLoadOp = StencilLoadOp;
        Attachment.Att.stencilStoreOp = StencilStoreOp;
        Attachment.Att.initialLayout = InitLayout;
        Attachment.Att.finalLayout = FinalLayout;

        Attachment.Layout = Image->Layout;
        return Attachment;
    }

// Frame Buffer
    void Image::BuildFrameBufferImages(VkExtent3D ImageExtent, FrameBuffer* Framebuffer, VkImageViewType ViewType)
    {
        // These Images are already allocated and instantiated, they are created with the Swapchain
        Image::AllocateImageView(VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT, &(Framebuffer->ImageBuffer));
        Image::BuildRenderTarget(VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, &Framebuffer->ImageBuffer, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE);
        Framebuffer->ImageBuffer.Type = RtType::RtColor;

        Image::AllocateImageView(ViewType, VK_IMAGE_ASPECT_DEPTH_BIT, &Framebuffer->DepthBuffer);
        Image::BuildRenderTarget(VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, &Framebuffer->DepthBuffer, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_DONT_CARE);
        Framebuffer->DepthBuffer.Type = RtType::RtDepth;
    }

    void Image::BuildFrameBuffer(VkRenderPass* RenderPass, VkExtent3D ImageExtent, FrameBuffer* Framebuffer)
    {
        VkFramebufferCreateInfo FBInfo;
        FBInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        FBInfo.width = ImageExtent.width;
        FBInfo.height = ImageExtent.height;

        FBInfo.attachmentCount = 2;
        VkImageView Attachments[2] = { Framebuffer->ImageBuffer.ImageView, Framebuffer->DepthBuffer.ImageView };

        FBInfo.pAttachments = Attachments;
        FBInfo.layers = 1;
    }

    AttDesc Image::BuildAttDesc(AllocatedImage* Image, VkAttachmentLoadOp LoadOp, VkAttachmentStoreOp StoreOp, VkImageLayout* EndLayout, VkAttachmentLoadOp StencilLoad, VkAttachmentStoreOp StencilStore)
    {
        AttDesc Attachment;
        Attachment.Att.samples = VK_SAMPLE_COUNT_1_BIT;

        Attachment.Att.format = Image->Format;
        Attachment.Att.samples = VK_SAMPLE_COUNT_1_BIT;
        Attachment.Att.loadOp = LoadOp;
        Attachment.Att.storeOp = StoreOp;
        Attachment.Att.stencilLoadOp = StencilLoad;
        Attachment.Att.stencilStoreOp = StencilStore;
        Attachment.Att.initialLayout = Image->Layout;

        if(EndLayout != nullptr)
        {
            Attachment.Att.finalLayout = *EndLayout;
        }
        else
        {
            Attachment.Att.finalLayout = Image->Layout;
        }

        Attachment.Layout = Image->Layout;

        return Attachment;
    }
