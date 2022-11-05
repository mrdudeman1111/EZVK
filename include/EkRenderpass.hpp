#pragma once

#include <EkTypes.hpp>
#include <set>

namespace Ek
{
    struct Subpass : public VkSubpassDescription
    {
        public:
        std::vector<AllocatedImage*> OurAttachments;
        uint32_t NumberOfAtts = 0;
        uint32_t LocalOffset = 0;
        VkSubpassDependency SubpassDependency;
        void Build(AllocatedImage* Attachments, AllocatedImage* DepthStencil, VkPipelineBindPoint BindPoint, uint32_t IndexOffset);
    };

    struct Renderpass
    {
        public:
        VkRenderPass RenderPass;
        // This input set var will contian a structure of { DepthAtt, ColorAtt, ColorAtt1, ResAtt }, They can be accessed VIA RtType
        std::set<RtType, AllocatedImage*> InputSets[0];
        Subpass* Subpasses;
        std::vector<AttDesc> Attachments;
        void Build();
    };

}
