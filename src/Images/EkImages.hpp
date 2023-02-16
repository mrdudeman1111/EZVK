#pragma once

#include <vector>
#include <iostream>
#include <string>

#include <vulkan/vulkan.h>

#include <vk_mem_alloc.h>


void ThrowError(const char* Error);

void Warn(const char* Error);

extern VkDevice GlobDevice;
extern VmaAllocator Allocator;
extern VkDebugUtilsMessengerEXT DebugMessenger;


// Explanation: DepthBuffer RenderTargets are depth stencils, only one of them can be attached to a renderpass
enum RtType
{
    RtDepth = 0b00001,
    RtColor = 0b00010,
    RtResolve = 0b00100,
    RtPreserve = 0b01000,
    RtInput = 0b10000
};

struct AttDesc
{
    public:
    AttDesc()
    {
        Att.flags = 0;
    }

    VkAttachmentDescription Att;
    int Type;
    VkImageLayout Layout;
};

struct AllocatedImage
{
    public:
    VkImage Image;
    VkImageView ImageView;
    VmaAllocation Allocation;

    VkFormat Format;
    VkImageLayout Layout = VK_IMAGE_LAYOUT_UNDEFINED;
    int Type;
};

// This is a wrapper structure for vkimages that are inteded to be used as RenderTargets/FrameBuffers. It is assumed that this is made with a VkImage
class FrameBuffer
{
    public:
    FrameBuffer()
    {}

    // This is just another image in gpu only memory ( unless otherwise specified in AllocateImage() ) that holds depth information. It's a depth stencil, meaning it's used for facial occlusion in renderpasses
    AllocatedImage ImageBuffer;

    AllocatedImage DepthBuffer;

    VkFramebuffer FB;

};

namespace Image
{
    void AllocateImageView(VkImageViewType ViewType, VkImageAspectFlagBits Aspects, AllocatedImage* PassedImage);

    bool AllocateImage(VkImageType ImageType, VkExtent3D Extent, VkFormat ImageFormat, VkImageLayout Layout, VmaMemoryUsage MemUse, uint32_t MipLevels, VkImageUsageFlags ImageUsage, AllocatedImage* PassedImage);

    AttDesc BuildRenderTarget(VkImageLayout InitLayout, VkImageLayout FinalLayout, AllocatedImage* Image, VkAttachmentLoadOp LoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE, VkAttachmentStoreOp StoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, VkAttachmentLoadOp StencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE, VkAttachmentStoreOp StencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE);

    AttDesc BuildAttDesc(AllocatedImage* Image, VkAttachmentLoadOp LoadOp, VkAttachmentStoreOp StoreOp, VkImageLayout* EndLayout, VkAttachmentLoadOp StencilLoad = VK_ATTACHMENT_LOAD_OP_DONT_CARE, VkAttachmentStoreOp StencilStore = VK_ATTACHMENT_STORE_OP_DONT_CARE);

    // This function will Allocate a color and depth buffer in gpu memory, Then it will build render targets(Create an attachment description for use with a subpass). after that it creates an image view for both buffers
    void BuildFrameBufferImages(VkExtent3D ImageExtent, FrameBuffer* Framebuffer, VkImageViewType ViewType = VK_IMAGE_VIEW_TYPE_2D);

    // This will fill a VkFrameBufferCreateInfo struct and then create The FrameBuffer (FB) with it
    void BuildFrameBuffer(VkRenderPass* RenderPass, VkExtent3D ImageExtent, FrameBuffer* Framebuffer);
}
