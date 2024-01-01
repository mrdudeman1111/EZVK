#pragma once

#include <Base/EkTypes.hpp>
#include <Images/EkImages.hpp>
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
        AllocatedImage* Resource; VkAttachmentReference Reference;
    };

    struct Renderpass;

    struct Subpass : public VkSubpassDescription
    {
        friend Renderpass;
        private:
        DeleteQueue CleanupQueue;


        // Quick explanation : Renderpass / Subpass attachments.
        // Renderpasses have several rendering operations to perform. So to make this easier and faster on the GPU, Vulkan introduced subpasses. Subpasses are small Bite sized rendering operations which you can intersperse throughout rendering operations.
        // Renderpasses take in "Attachment References". These attachment references are used to cut holes in the renderpass for input, You need these holes if you provide any form of input from outside the renderpass. Anything inside can be passed to the pipeline
        // So long as you have the proper VkPipelineLayout setup.

        // So Attachments are all stored in the renderpass, it contains a huge pool of Information and attachments, and the subpasses pick and choose what parts of that pool they want to use
        std::vector<uint32_t> ReserveIndices;
        std::vector<VkAttachmentReference*> Colors, Inputs, Resolves;
        uint32_t DepthAtt = -1;

        std::vector<VkSubpassDependency> Dependencies;

        uint32_t IndexOffset;
        uint32_t NumberOfAtts = 0;

        void PushAttachment(RenderpassResource* Resource, uint32_t* Iterator);

        public:

        void Build(std::vector<RenderpassResource>* pInputSets);
    };

    struct Renderpass
    {
        // Add a function to change out images in renderpass if they match the Attachment description used, as well as match the RtType
        // Idea: Create custom InitStruct for subpasses, and Create them through renderpass objects
        // Idea: Create a data structure to store all Attachments and their indices, pass these to the subpass so that it can add it's attachments.

        private:
        DeleteQueue CleanupQueue;
        uint32_t AttachmentIterator = 0;
        VkDevice* Device;
        class Window* pWindow;
        VkRenderPass RenderPass;

        // Contains references to the resource, as well as a AttachmentReference object for use with renderpass.
        std::vector<RenderpassResource> InputSets;

        public:
        std::vector<Subpass> Subpasses;

        Renderpass(VkDevice* PDev)
        {
            Device = PDev;
        }

        ~Renderpass()
        {
            CleanupQueue.Run();
        }

        void Build(Ek::Window* Window);

        void BuildSubpass(std::vector<VkSubpassDependency> Dependencies = {});

        void PushAttachment(AllocatedImage* Image, uint32_t SubpassIndex);

        Ek::Pipeline CreatePipeline(int Height, int Width);

        void Begin(Ek::CommandBase* CommandBuffer, VkFramebuffer* FrameBuffer, VkRect2D* RenderArea, std::vector<VkClearValue>* ClearValues);

        void End(Ek::CommandBase* CommandBuffer);
    };

}
