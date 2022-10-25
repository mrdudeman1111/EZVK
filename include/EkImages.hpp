#pragma once

#include <vector>
#include <iostream>
#include <string>

#include <vulkan/vulkan.h>

#include <vk_mem_alloc.h>

void ThrowError(const char* Error);

void Warn(const char* Error);

// Explanation: DepthBuffer RenderTargets are depth stencils, only one of them can be attached to a renderpass
enum RtType
{
    RtDepth = 0b0001,
    RtColor = 0b0010,
    RtResolve = 0b0100,
    RtPreserve = 0b1000
};

struct AllocatedImage
{
    public:
    VkImage Image;
    VkImageView ImageView;

    VkFormat Format;

    VkImageLayout Layout;

    VmaAllocation Allocation;
    VmaAllocator* AllocatorPtr;


    void AllocateImageView(VkDevice* Device, VkImageViewType ViewType)
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
        CreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        CreateInfo.subresourceRange.baseMipLevel = 0;
        CreateInfo.subresourceRange.levelCount = 1;
        CreateInfo.subresourceRange.baseArrayLayer = 0;
        CreateInfo.subresourceRange.layerCount = 1;

        if(vkCreateImageView(*Device, &CreateInfo, nullptr, &ImageView) != VK_SUCCESS)
        {
            ThrowError("Failed to Create Image View");
        }
    }

    bool AllocateImage(VkImageType ImageType, VkExtent3D Extent, VkFormat ImageFormat, VmaMemoryUsage MemUse, uint32_t MipLevels, VkImageCreateFlags ImageUsage, VkImageLayout ImgLayout)
    {
        Format = ImageFormat;
        Layout = ImgLayout;

        VkImageCreateInfo ImageInfo{};
        ImageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        ImageInfo.pNext = nullptr;
        ImageInfo.imageType = ImageType;
        ImageInfo.format = ImageFormat;
        ImageInfo.extent = Extent;
        ImageInfo.mipLevels = MipLevels;
        ImageInfo.arrayLayers = 1;
        ImageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        ImageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        ImageInfo.usage = ImageUsage;
        ImageInfo.initialLayout = ImgLayout;

        VmaAllocationCreateInfo AllocInfo{};
        AllocInfo.usage = MemUse;

        if(vmaCreateImage(*AllocatorPtr, &ImageInfo, &AllocInfo, &Image, &Allocation, nullptr) != VK_SUCCESS)
        {
            Warn("Failed to Create an image");
            return false;
        }

        return true;
    }

};

struct AttDesc : VkAttachmentDescription
{
    public:
    RtType Type;
    VkImageLayout Layout;
};

struct RenderTarget : AllocatedImage
{
    public:

    AttDesc AttachmentDesc;
    RtType Type;

    AttDesc Build(RtType RenderTargetType, VkExtent3D ImageExtent, VkFormat ImageFormat, VkImageCreateFlags ImageUse, VkImageLayout InitLayout, VkImageLayout FinalLayout, VkAttachmentLoadOp LoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE, VkAttachmentStoreOp StoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, VkAttachmentLoadOp StencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE, VkAttachmentStoreOp StencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE)
    {
        Type = RenderTargetType;
        Layout = InitLayout;
        AllocateImage(VK_IMAGE_TYPE_2D, ImageExtent, ImageFormat, VMA_MEMORY_USAGE_GPU_ONLY, 0, ImageUse, InitLayout);
        AttachmentDesc.format = Format;
        AttachmentDesc.samples = VK_SAMPLE_COUNT_1_BIT;
        AttachmentDesc.loadOp = LoadOp;
        AttachmentDesc.storeOp = StoreOp;
        AttachmentDesc.stencilLoadOp = StencilLoadOp;
        AttachmentDesc.stencilStoreOp = StencilStoreOp;
        AttachmentDesc.initialLayout = InitLayout;
        AttachmentDesc.finalLayout = FinalLayout;

        AttachmentDesc.Layout = Layout;
    }

    void BuildFrameBuffer(VkDevice* DevicePtr, VkExtent3D ImageExtent, VkFormat ImageFormat, VkImageViewType ViewType = VK_IMAGE_VIEW_TYPE_2D)
    {
        Build(RtType::RtColor, ImageExtent, ImageFormat, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_IMAGE_LAYOUT_PRESENT_SRC_KHR, VK_ATTACHMENT_LOAD_OP_CLEAR, VK_ATTACHMENT_STORE_OP_STORE);
        Type = RtType::RtColor;
        AllocateImageView(DevicePtr, ViewType);
    }

    void BuildDepthBuffer(VkDevice* DevicePtr, VkExtent3D ImageExtent, VkFormat ImageFormat, VkImageViewType ViewType = VK_IMAGE_VIEW_TYPE_2D)
    {
        Build(RtType::RtDepth, ImageExtent, ImageFormat, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE);
        Type = RtType::RtDepth;
        AllocateImageView(DevicePtr, ViewType);
    }
    
};
