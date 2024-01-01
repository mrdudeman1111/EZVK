#include <Rendering/EkRenderpass.hpp>
#include <Base/EkWindow.hpp>

void Ek::Subpass::Build(std::vector<RenderpassResource>* pInputSets)
{
    // Use AttIterator as Index. AttIterator is the index of the last attachment we processed, meaning if we continue from there
    colorAttachmentCount = Colors.size();
    pColorAttachments = *Colors.data();
    inputAttachmentCount = Inputs.size();
    pInputAttachments = *Inputs.data();
    preserveAttachmentCount = ReserveIndices.size();
    pPreserveAttachments = ReserveIndices.data();
    pResolveAttachments = *Resolves.data();

    pDepthStencilAttachment = &pInputSets->at(DepthAtt).Reference;
}

void Ek::Subpass::PushAttachment(RenderpassResource* Resource, uint32_t* Iterator)
{
    *Iterator++;
    if(Resource->Resource->Type & RtColor)
    {
        Colors.push_back(&Resource->Reference);
    }

    else if(Resource->Resource->Type & RtDepth)
    {
        DepthAtt = *Iterator;
    }

    else if(Resource->Resource->Type & RtInput)
    {
        Inputs.push_back(&Resource->Reference);
    }

    else if(Resource->Resource->Type & RtResolve)
    {
        Resolves.push_back(&Resource->Reference);
    }

    else
    {
        throw std::runtime_error("Failed to create subpass attachment, Uknown Attachment Type");
    }

    NumberOfAtts++;

    if(Resource->Resource->Type & RtPreserve)
    {
        ReserveIndices.push_back(*Iterator);
    }
}

void Ek::Renderpass::PushAttachment(AllocatedImage* Image, uint32_t SubpassIndex)
{
    VkAttachmentReference Ref;
    Ref.attachment = AttachmentIterator;
    Ref.layout = Image->Layout;

    RenderpassResource Resource;
    Resource.Resource = Image;
    Resource.Reference = Ref;

    InputSets.push_back(Resource);

    Subpasses[SubpassIndex].PushAttachment(&Resource, &AttachmentIterator);
}

void Ek::Renderpass::BuildSubpass(std::vector<VkSubpassDependency> Dependencies)
{
    Ek::Subpass Subpass{};
    Subpasses.push_back(Subpass);
}

Ek::Pipeline Ek::Renderpass::CreatePipeline(int Height, int Width)
{
    Ek::Pipeline Pipe(Device, &RenderPass, Height, Width);
    return Pipe;
}

// Pointer to an array of Subpasses
void Ek::Renderpass::Build(Ek::Window* Window)
{
    VkRenderPassCreateInfo RenderPassCI{};
    RenderPassCI.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

    std::vector<VkAttachmentDescription*> Descriptions(InputSets.size());
    for(uint32_t i = 0; i < InputSets.size(); i++)
    {
        Descriptions[i] = &InputSets[i].Resource->Description;
    }

    RenderPassCI.attachmentCount = Descriptions.size();
    RenderPassCI.pAttachments = *Descriptions.data();

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
