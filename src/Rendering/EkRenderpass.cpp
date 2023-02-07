#include <Rendering/EkRenderpass.hpp>

    void Ek::Subpass::Build(std::vector<AllocatedImage>* Attachments, AllocatedImage* DepthStencil, VkPipelineBindPoint BindPoint, uint32_t IndexOffset, VkSubpassDependency* Depend)
    {
        if(Depend == nullptr)
        {
            SubpassDependency = Depend;
        }

        if(Attachments != nullptr)
        {
            LocalOffset = IndexOffset;

            // Load Attachments
                uint32_t Index = LocalOffset;
                std::vector<uint32_t> Preserves;

                for(uint32_t i = 0; i < Attachments->size(); i++)
                {
                    OurAttachments.push_back(&Attachments->at(i));

                    if(Attachments->at(i).Type & RtType::RtColor)
                    {
                        VkAttachmentReference ColorRef;
                        ColorRef.attachment = Index;
                        Index++;
                        ColorRef.layout = Attachments->at(i).Layout;
                        Colors.push_back(ColorRef);
                    }

                    if(Attachments->at(i).Type & RtType::RtDepth)
                    {
                        std::cout << "Depth Attachment Has been loaded into a subpass and will be passed to a Renderpass";
                    }

                    if(Attachments->at(i).Type & RtType::RtResolve)
                    {
                        VkAttachmentReference ResolveRef;
                        ResolveRef.attachment = Index;
                        Index++;
                        ResolveRef.layout = Attachments->at(i).Layout;
                        Resolves.push_back(ResolveRef);
                    }

                    if(Attachments->at(i).Type & RtType::RtPreserve)
                    {
                        Preserves.push_back(i);
                    }
                }

            colorAttachmentCount = Colors.size();
            pColorAttachments = Colors.data();

            if(Resolves.size() > 0)
            {
                pResolveAttachments = Resolves.data();
            }

            preserveAttachmentCount = Preserves.size();
            pPreserveAttachments = Preserves.data();
            inputAttachmentCount = 0;

            if(DepthStencil != nullptr)
            {
                DepthAtt.attachment = Index;
                Index++;
                DepthAtt.layout = DepthStencil->Layout;
                pDepthStencilAttachment = &DepthAtt;
                OurAttachments.push_back(DepthStencil);
            }
        }
        else
        {
            ThrowError("Tried to create a subpass with no attachments");
        }
        pipelineBindPoint = BindPoint;
    }

    void Ek::Renderpass::Build(Ek::Subpass* Subpasses)
    {
        if(Subpasses != nullptr)
        {
            std::vector<VkSubpassDependency> Dependencies(0);
            int SubpassCount = sizeof(*Subpasses)/sizeof(Subpasses[0]);
            std::vector<VkAttachmentDescription> Attachments;
            for(uint32_t i = 0; i < SubpassCount; i++)
            {
                for(uint32_t x = 0; x < Subpasses[i].OurAttachments.size(); x++)
                {
                    Attachments.push_back(Subpasses[i].OurAttachments[x]->AttachmentDesc.Att);
                }
                
                if(Subpasses[i].SubpassDependency != nullptr)
                {
                    Dependencies.push_back(*Subpasses[i].SubpassDependency);
                }
            }

            VkRenderPassCreateInfo RCI{};
            RCI.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
            RCI.subpassCount = SubpassCount;
            RCI.pSubpasses = Subpasses;
            RCI.attachmentCount = Attachments.size();
            
            RCI.pAttachments = Attachments.data();

            if(Dependencies.size() == 0)
            {
                RCI.dependencyCount = Dependencies.size();
                RCI.pDependencies = Dependencies.data();
            }

            VkResult Err = vkCreateRenderPass(GlobDevice, &RCI, nullptr, &RenderPass);
            if(Err != VK_SUCCESS)
            {
                std::cout << Err << std::endl; 
                ThrowError("Failed to create render pass");
            }
        }
    }

    void Ek::Renderpass::Begin(Ek::CommandBase* CommandBuffer, VkFramebuffer* FrameBuffer, VkRect2D* RenderArea, std::vector<VkClearValue>* ClearValues)
    {
        VkRenderPassBeginInfo RenderPassBegin{};
        RenderPassBegin.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        RenderPassBegin.framebuffer = *FrameBuffer;
        RenderPassBegin.clearValueCount = ClearValues->size();
        RenderPassBegin.pClearValues = ClearValues->data();
        RenderPassBegin.renderArea = *RenderArea;
        RenderPassBegin.renderPass = RenderPass;

        // Invalid FrameBuffer
        vkCmdBeginRenderPass(CommandBuffer->CmdBuffer, &RenderPassBegin, VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE);
    }

    void Ek::Renderpass::End(Ek::CommandBase* CommandBuffer)
    {
        vkCmdEndRenderPass(CommandBuffer->CmdBuffer);
    }
