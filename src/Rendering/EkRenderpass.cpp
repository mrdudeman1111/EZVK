#include <Rendering/EkRenderpass.hpp>

void Ek::Subpass::Build(std::vector<AttDesc>* Attachments, AllocatedImage* DepthStencil, VkPipelineBindPoint BindPoint, uint32_t IndexOffset, VkSubpassDependency* Depend = nullptr)
{
    pipelineBindPoint = BindPoint;
    for(uint32_t i = 0; i < Attachments->size(); i++)
    {
        // sort attachments, into color, depth, input, resolve
        if(Attachments->at(1).Type & RtColor)
        {
        }
    }
}

// Pointer to an array of Subpasses
void Ek::Renderpass::Build(Ek::Subpass* Subpasses)
{
}
