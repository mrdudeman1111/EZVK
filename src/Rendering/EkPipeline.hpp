#pragma once

#include <Base/EkTypes.hpp>

// Instead 
namespace Ek
{
    enum ShaderType
    {
        eShaderVert,
        eShaderFrag,
        eShaderGeometry,
        eShaderCompute,
        eShaderTesselation
    };

    // Add Push Constant support
    struct Shader
    {
        friend class Pipeline;
        friend class Material;
        friend class Device;
        public:
        Shader(VkDevice* Device);

        ~Shader()
        {
            CleanupQueue.Run();
        }

        void AddImage(uint32_t Binding, VkDescriptorType Type, AllocatedImage* Image, uint32_t DescriptorCount);
        void AddBuffer(uint32_t Binding, VkDescriptorType Type, VkBuffer* Buffer, uint32_t DescriptorCount);

        // DEPRECATED: This is now handled by Material,
        // void BuildShaderLayout();

        // Shader Name is the name of the entrypoint function in the shader (the example shader entrypoint functions are main so This name will be name)
        const char* ShaderEntryPoint;
        VkShaderStageFlagBits Stage;

        ShaderType Type;

        private:
        // Descriptor Information
        std::vector<VkDescriptorSetLayout> DescriptorLayouts;
        std::vector<VkDescriptorSetLayoutBinding> DescriptorBindings;

        // std::vector<VkDescriptorSet> DescriptorSets;

        std::vector<VkDescriptorPoolSize> PoolSizes;

        std::vector<AllocatedImage*> Images;
        std::vector<VkBuffer*> Buffers;

        VkDevice* pDev;

        DeleteQueue CleanupQueue;

        uint32_t LayoutIterator = 0;

        // This is provided by the Device during creation.
        VkShaderModule ShaderModule;
    };

    // Descriptors act like binding points in Opengl. This should be part of every material
    class Material
    {
        friend class Pipeline;
        public:

        Material(VkDevice* Device);

        ~Material();

        void AddShader(Ek::Shader* Shader);

        // Depending on what ShaderType is passed, we pass the following parameters to the shader at that stage
        void AddShaderInput(ShaderType ShaderType, uint32_t Location, VkDescriptorType DescriptorType, void* Input, uint32_t DescriptorCount);

        void Build(Ek::BasicVertex* VertexClass);

        private:
        VkDevice* pDev;
        DeleteQueue DelQueue;
        Ek::BasicVertex* pVertexClass;

        std::vector<AllocatedImage*> InImage;
        std::vector<AllocatedBuffer*> InBuffer;

        VkPipelineVertexInputStateCreateInfo VertexInput;

        VkPipelineLayout PipelineLayout;

        std::vector<Shader> Shaders;
        std::vector<VkPipelineShaderStageCreateInfo> ShaderStages;

        VkDescriptorPool DescriptorPool;
        std::vector<VkDescriptorSet> Descriptors;
        std::vector<VkDescriptorSetLayout> Layouts;
    };

    // Pipelines are very interesting. But first, Renderpasses. Renderpasses handle networking input and output. They are often used to specify which framebuffer to render to.
    // Pipelines Specify where to render to in the image. They also specify what shaders to use.
    class Pipeline
    {
        public:
        Pipeline(){};

        Pipeline(VkDevice* Dev, VkRenderPass* Rp, uint32_t Height, uint32_t Width) : p_Renderpass{Rp}, Height{Height}, Width{Width}
        {
            p_Dev = Dev;
        }

        void Build(Material* Mat, uint32_t SubpassToUse, Ek::BasicVertex* VertexClass);

        private:

        VkDevice* p_Dev;

        std::vector<Shader*> Shaders;

        uint32_t Height, Width;

        VkRenderPass* p_Renderpass;
        VkPipeline VkPipe;
        VkPipelineLayout VkPipeLayout;

        DeleteQueue CleanupQueue;
        VkViewport ViewPort;
    };
}
