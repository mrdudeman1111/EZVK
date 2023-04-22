#pragma once

#include <Base/EkTypes.hpp>

namespace Ek
{
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

        void AddShaderInput(uint32_t Location, VkDescriptorType Type, uint32_t InputCount = 1);

        void Build();

        // DEPRECATED: This is now handled by Material,
        // void BuildShaderLayout();

        // Shader Name is the name of the entrypoint function in the shader (the example shader entrypoint functions are main so This name will be name)
        const char* ShaderEntryPoint;
        VkShaderStageFlagBits Stage;

        private:
        // Descriptor Information
        std::vector<VkDescriptorSetLayout> DescriptorLayouts;
        std::vector<VkDescriptorSetLayoutBinding> DescriptorBindings;

        // std::vector<VkDescriptorSet> DescriptorSets;

        std::vector<VkDescriptorPoolSize> PoolSizes;

        VkDevice* pDev;

        DeleteQueue CleanupQueue;

        uint32_t LayoutIterator = 0;
        VkShaderModule ShaderModule;
    };

    class PipeLayout
    {
        public:
        std::vector<VkDescriptorSetLayout> Descriptors;
        std::vector<VkPushConstantRange> PushConstants;
    };

    // Descriptors act like binding points in Opengl. This should be part of every material
    class Material
    {
        friend class Pipeline;
        public:

        Material(VkDevice* Device);

        ~Material()
        {
            DelQueue.Run();
        }

        void AddShader(Ek::Shader* Shader);

        void Build();

        private:
        VkDevice* pDev;

        VkDescriptorPool DescriptorPool;

        PipeLayout GenLayout;

        DeleteQueue DelQueue;

        std::vector<Shader> Shaders;
        std::vector<VkDescriptorSet> Descriptors;
        std::vector<VkDescriptorSetLayout> Layouts;
    };

    class Pipeline
    {
        public:
        Pipeline(){};

        Pipeline(VkDevice* Dev, VkRenderPass* Rp, uint32_t Height, uint32_t Width) : p_Renderpass{Rp}, Height{Height}, Width{Width}
        {
            p_Dev = Dev;
        }

        ~Pipeline()
        {
            CleanupQueue.Run();
        }

        void Build(Material* Mat, uint32_t SubpassToUse, Ek::BasicVertex* VertexClass);

        private:
        VkDevice* p_Dev;

        std::vector<Shader*> Shaders;

        PipeLayout PipelineLayout;

        uint32_t Height, Width;

        VkRenderPass* p_Renderpass;
        VkPipeline VkPipe;
        VkPipelineLayout VkPipeLayout;

        DeleteQueue CleanupQueue;
        VkViewport ViewPort;
    };
}
