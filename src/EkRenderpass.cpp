#include <EkRenderpass.hpp>

    void Ek::Subpass::Build(AllocatedImage* Attachments, AllocatedImage* DepthStencil, VkPipelineBindPoint BindPoint, uint32_t IndexOffset)
    {
        if(Attachments != nullptr)
        {
            NumberOfAtts = sizeof(Attachments)/sizeof(Attachments[0]) + 1;
            LocalOffset = IndexOffset;

            // Load Attachments
                std::vector<VkAttachmentReference> Colors, Depths, Resolves;
                uint32_t Index = LocalOffset;
                std::vector<uint32_t> Preserves;

                for(uint32_t i = 0; i < sizeof(Attachments)/sizeof(Attachments[0]); i++)
                {
                    OurAttachments.push_back(&Attachments[i]);

                    if(Attachments[i].Type & RtColor)
                    {
                        VkAttachmentReference ColorRef;
                        ColorRef.attachment = Index;
                        Index++;
                        ColorRef.layout = Attachments[i].Layout;
                        Colors.push_back(ColorRef);
                    }

                    if(Attachments[i].Type & RtDepth)
                    {
                        std::cout << "Depth Attachment Has been loaded into a subpass and will be passed to a Renderpass";
                    }

                    if(Attachments[i].Type & RtResolve)
                    {
                        VkAttachmentReference ResolveRef;
                        ResolveRef.attachment = Index;
                        Index++;
                        ResolveRef.layout = Attachments[i].Layout;
                        Resolves.push_back(ResolveRef);
                    }
                    
                    if(Attachments[i].Type & RtPreserve)
                    {
                        Preserves.push_back(i);
                    }
                }

            colorAttachmentCount = Colors.size();
            pColorAttachments = Colors.data();
            pResolveAttachments = Resolves.data();
            preserveAttachmentCount = Preserves.size();
            pPreserveAttachments = Preserves.data();
            inputAttachmentCount = 0;

            if(DepthStencil != nullptr)
            {
                VkAttachmentReference DepthAtt{};
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

    void Ek::Renderpass::Build()
    {
        for(uint32_t i = 0; i < sizeof(*Subpasses)/sizeof(Subpasses[0]); i++)
        {
            for(uint32_t x = 0; x < Subpasses[i].OurAttachments.size(); x++)
            {
                Attachments.push_back(Subpasses[i].OurAttachments[x]->AttachmentDesc);
            }
        }

        std::vector<VkSubpassDependency> Dependencies;
        for(uint32_t i = 0; i < sizeof(*Subpasses)/sizeof(Subpasses[0]); i++)
        {
            Dependencies.push_back(Subpasses[i].SubpassDependency);
        }

        VkRenderPassCreateInfo RCI{};
        RCI.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        RCI.attachmentCount = Attachments.size();
        RCI.pAttachments = Attachments.data();
        RCI.dependencyCount = Dependencies.size();
        RCI.pDependencies = Dependencies.data();
    }
