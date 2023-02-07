#pragma once

#include <Base/EkTypes.hpp>
#include <set>

namespace Ek
{
    struct Subpass : public VkSubpassDescription
    {
        public:
        DeleteQueue CleanupQueue;
        
        std::vector<AllocatedImage*> OurAttachments;
        std::vector<VkAttachmentReference> Colors, Depths, Resolves;
        VkAttachmentReference DepthAtt;
        
        uint32_t NumberOfAtts = 0;
        uint32_t LocalOffset = 0;

        VkSubpassDependency* SubpassDependency;

        void Build(std::vector<AllocatedImage>* Attachments, AllocatedImage* DepthStencil, VkPipelineBindPoint BindPoint, uint32_t IndexOffset, VkSubpassDependency* Depend = nullptr);
    };

    struct Renderpass
    {
        public:
        ~Renderpass()
        {
            CleanupQueue.Run();
        }

        VkRenderPass RenderPass;
        DeleteQueue CleanupQueue;

        // This input set var will contain a structure of { DepthAtt, ColorAtt, ColorAtt1, ResAtt }, They can be accessed VIA RtType
        std::set<RtType, AllocatedImage*> InputSets[0];

        Subpass* Subpasses;
        void Build(Ek::Subpass* Subpasses);

        void Begin(Ek::CommandBase* CommandBuffer, VkFramebuffer* FrameBuffer, VkRect2D* RenderArea, std::vector<VkClearValue>* ClearValues);

        void End(Ek::CommandBase* CommandBuffer);
    };

}
