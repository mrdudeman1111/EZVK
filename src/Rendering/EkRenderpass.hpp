#pragma once

#include <Base/EkTypes.hpp>
#include <Rendering/EkPipeline.hpp>
#include <set>
#include <map>

/* 
    Keep in mind that when you give a renderpass allocated images as params.
    It stores pointers to those resource, That resource's lifetime is managed by you.
    To change the renderpass (taking or adding a resource) requires you to create the Renderpass.
*/

namespace Ek
{
    struct SubpassCI
    {
        public:
        VkPipelineBindPoint PipeBindPoint;
        VkSubpassDependency* Dependencies;
    };

    struct RenderpassResource
    {
        AllocatedImage* Resource;
        VkAttachmentReference Reference;
    };

    struct Subpass : public VkSubpassDescription
    {
        public:
        DeleteQueue CleanupQueue;

        std::vector<VkAttachmentReference> Colors, Inputs, Resolves;
        std::vector<uint32_t> ReserveIndices;
        uint32_t DepthAtt = -1;

        std::vector<VkSubpassDependency> Dependencies;

        // This variable stores the index of the first attachment in InputSets.
        uint32_t IndexOffset;
        uint32_t NumberOfAtts = 0;

        void Build(std::vector<RenderpassResource>* InputSets, uint32_t* AttIterator, std::vector<VkSubpassDependency>* Depends = {});
    };

    struct Renderpass
    {
        // Add a function to change out images in renderpass if they match the Attachment description used, as well as match the RtType
        // Idea: Create custom InitStruct for subpasses, and Create them through renderpass objects
        // Idea: Create a data structure to store all Attachments and their indices, pass these to the subpass so that it can add it's attachments.

        private:
        DeleteQueue CleanupQueue;
        uint32_t AttachmentIterator = 0;;
        VkDevice* Device;
        int Height, Width;

        // Contains references to the resource, as well as a AttachmentReference object for use with renderpass.
        std::vector<RenderpassResource> InputSets;

        std::vector<Subpass> Subpasses;

        public:
        Renderpass(VkDevice* PDev)
        {
            Device = PDev;
        }

        ~Renderpass()
        {
            CleanupQueue.Run();
        }

        VkRenderPass RenderPass;

        void Build();

        void BuildSubpass(std::vector<AllocatedImage*> Attachments, std::vector<VkSubpassDependency> Dependencies = {});

        Ek::Pipeline CreatePipeline(int Height, int Width);

        void Begin(Ek::CommandBase* CommandBuffer, VkFramebuffer* FrameBuffer, VkRect2D* RenderArea, std::vector<VkClearValue>* ClearValues);

        void End(Ek::CommandBase* CommandBuffer);
    };

}
