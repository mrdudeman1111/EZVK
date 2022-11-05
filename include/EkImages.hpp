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

struct AttDesc : VkAttachmentDescription
{
    public:
    RtType Type;
    VkImageLayout Layout;
};

struct AllocatedImage
{
    public:
    VkImage Image;
    VkImageView ImageView;
    
    VkFormat Format;

    VkImageLayout Layout = VK_IMAGE_LAYOUT_UNDEFINED;

    VmaAllocation Allocation;


    AttDesc AttachmentDesc;
    uint8_t Type;

    // This function will fill the AttachmentDesc member with information provided by the call, Sample count is always 1
};

struct RenderTarget
{
    public:
    AllocatedImage Image;
};

// This is a wrapper structure for vkimages that are inteded to be used as RenderTargets/FrameBuffers. It is assumed that this is made with a VkImage
struct FrameBuffer
{

    public:
    // This is just another image in gpu only memory ( unless otherwise specified in AllocateImage() ) that holds depth information. It's a depth stencil, meaning it's used for facial occlusion in renderpasses
    AllocatedImage ImageBuffer;
    AllocatedImage DepthBuffer;
    VkFramebuffer FB;

    AttDesc GetColorAttachments();

    AttDesc GetDepthAttachments();
    
    FrameBuffer(AllocatedImage PassedColorBuffer, AllocatedImage PassedDepthBuffer)
    {
        ImageBuffer = PassedColorBuffer;
        DepthBuffer = PassedDepthBuffer;
    }

    FrameBuffer()
    {

    }

};

namespace Image
{
    void AllocateImageView(VkImageViewType ViewType, VkImageAspectFlagBits Aspects, AllocatedImage* PassedImage);

    bool AllocateImage(VkImageType ImageType, VkExtent3D Extent, VkFormat ImageFormat, VkImageLayout Layout, VmaMemoryUsage MemUse, uint32_t MipLevels, VkImageUsageFlags ImageUsage, AllocatedImage* PassedImage);

    void BuildRenderTarget(VkImageLayout InitLayout, VkImageLayout FinalLayout, AllocatedImage* Image, VkAttachmentLoadOp LoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE, VkAttachmentStoreOp StoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, VkAttachmentLoadOp StencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE, VkAttachmentStoreOp StencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE);

    // This function will Allocate a color and depth buffer in gpu memory, Then it will build render targets(Create an attachment description for use with a subpass). after that it creates an image view for both buffers
    void BuildFrameBufferImages(VkExtent3D ImageExtent, VkFormat ImageFormat, FrameBuffer* Framebuffer, VkImageViewType ViewType = VK_IMAGE_VIEW_TYPE_3D);

    // This will fill a VkFrameBufferCreateInfo struct and then create The FrameBuffer (FB) with it
    void BuildFrameBuffer(VkRenderPass* RenderPass, VkExtent3D ImageExtent, FrameBuffer* Framebuffer);
}
