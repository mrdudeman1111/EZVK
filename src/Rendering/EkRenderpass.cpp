#include <Rendering/EkRenderpass.hpp>

void Ek::Subpass::Build(std::vector<RenderpassResource>* InputSets, uint32_t* AttIterator, std::vector<VkSubpassDependency>* Depends)
{
    // Use AttIterator as Index. AttIterator is the index of the last attachment we processed, meaning if we continue from there
    uint32_t i;
    for(i = *AttIterator; i < InputSets->size()-*AttIterator; i++)
    {
        RenderpassResource* Resource = &InputSets->at(*AttIterator);
        if(Resource->Resource->Type & RtColor)
        {
            VkAttachmentReference AttRef;
            AttRef.attachment = i;
            AttRef.layout = Resource->Resource->Layout;
            Colors.push_back(Resource->Reference);
        }

        else if(Resource->Resource->Type & RtInput)
        {
            VkAttachmentReference AttRef;
            AttRef.attachment = i;
            AttRef.layout = Resource->Resource->Layout;
            Inputs.push_back(Resource->Reference);
        }

        else if(Resource->Resource->Type & RtResolve) 
        {
            VkAttachmentReference AttRef;
            AttRef.attachment = i;
            AttRef.layout = Resource->Resource->Layout;
            Resolves.push_back(Resource->Reference);
        }

        else if(Resource->Resource->Type & RtDepth)
        {
            throw std::runtime_error("Failed to Create Subpass.\n There was a depth buffer in the AttachmentImages in the SubpassCI passed from the renderpass. This means you passed a DepthBuffer in the Ek::RenderPass::BuildSubpass(...). Don't, A Subpass can only have one depthstencil attachment.");
        }

        if(Resource->Resource->Type & RtPreserve)
        {
            ReserveIndices.push_back(i);
        }

        if(Resource->Resource->Type & RtDepth)
        {
            DepthAtt = i;
        }
    }

    for(uint32_t i = 0; i < Depends->size(); i++)
    {
        Dependencies[i] = Depends->at(i);
    }

    *AttIterator = i;

    colorAttachmentCount = Colors.size();

    pColorAttachments = Colors.data();
    inputAttachmentCount = Inputs.size();
    pInputAttachments = Inputs.data();
    pResolveAttachments = Resolves.data();
    preserveAttachmentCount = ReserveIndices.size();
    pPreserveAttachments = ReserveIndices.data();
    pDepthStencilAttachment = &InputSets->at(DepthAtt).Reference;
}

void Ek::Renderpass::BuildSubpass(std::vector<AllocatedImage*> Attachments, std::vector<VkSubpassDependency> Dependencies)
{
    Ek::Subpass Subpass;

    for(uint32_t i = 0; i< Attachments.size(); i++)
    {
        VkAttachmentReference AttRef;

        AttRef.attachment = AttachmentIterator;
        AttRef.layout = Attachments[i]->Layout;

        InputSets.push_back({});
        InputSets[i].Reference = AttRef;
        InputSets[i].Resource = Attachments[i];
    }

    Subpass.Build(&InputSets, &AttachmentIterator, &Dependencies);
    Subpasses.push_back(Subpass);
}

Ek::Pipeline Ek::Renderpass::CreatePipeline(int Height, int Width)
{
    Ek::Pipeline Pipe(Device, &RenderPass, Height, Width);
    return Pipe;
}

// Pointer to an array of Subpasses
void Ek::Renderpass::Build()
{
    VkRenderPassCreateInfo RenderPassCI{};
    RenderPassCI.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    RenderPassCI.attachmentCount = InputSets.size();

    std::vector<VkSubpassDependency> Deps;
    for(uint32_t i = 0; i < Subpasses.size(); i++)
    {
        for(uint32_t x = 0; x < Subpasses[i].Dependencies.size(); x++)
        {
            Deps.push_back(Subpasses[i].Dependencies[x]);
        }
    }

    if(!Deps.empty())
    {
        RenderPassCI.dependencyCount = Deps.size();
        RenderPassCI.pDependencies = Deps.data();
    }

    RenderPassCI.subpassCount = Subpasses.size();
    RenderPassCI.pSubpasses = Subpasses.data();

    if(vkCreateRenderPass(*Device, &RenderPassCI, nullptr, &RenderPass) != VK_SUCCESS)
    {
        throw std::runtime_error("Failed to create a renderpass");
    }
}

void Ek::Renderpass::Begin(Ek::CommandBase* CommandBuffer, VkFramebuffer* FrameBuffer, VkRect2D* RenderArea, std::vector<VkClearValue>* ClearValues)
{
    VkRenderPassBeginInfo BeginInf{};
    BeginInf.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    BeginInf.framebuffer = *FrameBuffer;
    BeginInf.clearValueCount = ClearValues->size();
    BeginInf.pClearValues = ClearValues->data();
    BeginInf.renderArea = *RenderArea;
    BeginInf.renderPass = RenderPass;

    vkCmdBeginRenderPass(CommandBuffer->CmdBuffer, &BeginInf, VK_SUBPASS_CONTENTS_INLINE);
}

void Ek::Renderpass::End(Ek::CommandBase* CommandBuffer)
{
    vkCmdEndRenderPass(CommandBuffer->CmdBuffer);
}
