#pragma once

#include <vulkan/vulkan.h>
#include <Images/EkImages.hpp>

// GLM/GLFW Includes
    #include <glm/vec4.hpp>
    #include <glm/mat4x4.hpp>
    #include <glm/ext/matrix_transform.hpp>
    #include <glm/ext/matrix_clip_space.hpp>
    #include <glm/gtx/string_cast.hpp>

// std namespace includes
    #include <memory>
    #include <fstream>
    #include <chrono>
    #include <cstdarg>
    #include <array>
    #include <queue>
    #include <stack>
    #include <functional>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

// Forward declared Helper functions
    std::vector<char> ReadFile(const char* FileName);

    void ThrowError(const char* ErrorMsg);

    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData, void *pUserData)
    {
        if(messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        {
            std::cout << "validation layer: " << pCallbackData->pMessage << std::endl;
        }
        return VK_FALSE;
    }

// Types enum VertexType{VTX_Basic, VTX_Rigged};

    enum CommandBufferUsage
    {
        OneTime = 0x00000001,
        RenderPass = 0x00000002,
        Simultaneous = 0x00000004
    };

    typedef uint32_t ivec3[3];

// Allocated Types:
    struct AllocatedBuffer
    {
        VkBuffer Buffer;
        VmaAllocation Allocation;
    };

    struct DeleteQueue
    {
        std::stack<std::function<void()>> DeletionQueue;

        void operator() (std::function<void()> const& DeleteLambda)
        {
            DeletionQueue.push(DeleteLambda);
        }

        void Run()
        {
            int QueueSize = DeletionQueue.size();
            for(uint32_t i = 0; i < QueueSize; i++)
            {
                auto Func = DeletionQueue.top();
                DeletionQueue.pop();
                Func();
            }
        }
    };

    extern DeleteQueue DelQueue;

namespace Ek
{

// Create Queue Buffer, and then create record buffer, so the user has the choice to just record their own command buffer, or just create a queue of calls
// And then record all the queued calls with the bake function
    class CommandBase
    {
        public:
        std::string Name;
        VkCommandBuffer CmdBuffer;
    };

    class CommandQueue : public CommandBase
    {
        public:
        std::queue<std::function<void()>> Queue;
        VkCommandBufferBeginInfo BeginInfo;

        CommandQueue(CommandBufferUsage Usage)
        {
            BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            BeginInfo.flags = Usage;
        }

        void Allocate(VkDevice* Dev, VkCommandPool* Pool, uint32_t Priority)
        {
            VkCommandBufferAllocateInfo AllocInfo{};
            AllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            AllocInfo.commandPool = *Pool;

            switch(Priority)
            {
                case 0:
                    AllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                    break;
                case 1:
                    AllocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
                    break;
                default:
                    AllocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
                    break;
            }

            AllocInfo.commandBufferCount = 1;

            if(vkAllocateCommandBuffers(*Dev, &AllocInfo, &CmdBuffer) != VK_SUCCESS)
            {
                ThrowError("Unexpectedly couldn't Allocate Memmory for a command buffer, perhaps the pool ran out of space");
            }
        }

        // Always pass a lambda with no parameters or return types, just wrap all the commands you want run into a labmda object and pass it.
        void operator() (std::function<void()> Command)
        {
            Queue.push(Command);
        }

        // Really what we're doing here is recording the command buffer.
        void Bake()
        {
            vkBeginCommandBuffer(CmdBuffer, &BeginInfo);
            for(uint32_t i = 0; i < Queue.size(); i++)
            {
                auto Func = Queue.front();
                Queue.pop();
                Func();
            }
            vkEndCommandBuffer(CmdBuffer);
        }

    };

    class CommandBuffer : public CommandBase
    {
        public:
        VkCommandBufferBeginInfo BeginInfo;

        CommandBuffer(CommandBufferUsage Usage)
        {
            BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            BeginInfo.pNext = NULL;
            BeginInfo.flags = Usage;
            BeginInfo.pInheritanceInfo = nullptr;
        }

        void Begin()
        {
            vkBeginCommandBuffer(CmdBuffer, &BeginInfo);
        }

        void End()
        {
            vkEndCommandBuffer(CmdBuffer);
        }

    };

}

namespace Ek
{
    struct CmdPool
    {
        public:
        VkCommandPool CommandPool;
        DeleteQueue CleanupQueue;
        VkDevice* pDev;

        CmdPool()
        {}

        CmdPool(VkDevice* Dev, uint32_t GraphicsQueueFamilyIndex, DeleteQueue* DeletionQueue)
        {
            Create(Dev, GraphicsQueueFamilyIndex, DeletionQueue);
        }

        ~CmdPool()
        {
            CleanupQueue.Run();
        }

        void Create(VkDevice* Dev, uint32_t GraphicsQueueFamilyIndex, DeleteQueue* DeletionQueue)
        {
            pDev = Dev;

            VkCommandPoolCreateInfo PoolInfo{};
            PoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
            PoolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
            PoolInfo.queueFamilyIndex = GraphicsQueueFamilyIndex;

            if(vkCreateCommandPool(*Dev, &PoolInfo, nullptr, &CommandPool) != VK_SUCCESS)
            {
                ThrowError("Failed to create EkCmdPool");
            }

            VkDevice* DevHandle = Dev;
            VkCommandPool* CmdPool = &CommandPool;
            CleanupQueue([DevHandle, CmdPool](){ vkDestroyCommandPool(*DevHandle, *CmdPool, nullptr); std::cout << "Destroyed A command pool\n"; });
        }

        // Priority can be 0 or 1, anything else throws error. 0 being primary, and therefore prioritized, and 1 being secondary, and therefore less important, (it's a little less slower than primary, it also gets less resources allocated to it)
        Ek::CommandQueue AllocateCmdQueue(int Priority, CommandBufferUsage Usage)
        {
            switch(Priority)
            {
                case 0: 
                {
                    Ek::CommandQueue NewCmdBuffer(Usage);
                    NewCmdBuffer.Allocate(pDev, &CommandPool, 0);
                    CleanupQueue([this, &NewCmdBuffer](){ vkFreeCommandBuffers(*pDev, CommandPool, 1, &NewCmdBuffer.CmdBuffer); std::cout << "Deleted CommandBuffer.\n"; });
                    return NewCmdBuffer;
                    break;
                }

                case 1:
                {
                    Ek::CommandQueue NewCmdBuffer(Usage);
                    NewCmdBuffer.Allocate(pDev, &CommandPool, 1);
                    CleanupQueue([this, &NewCmdBuffer](){ vkFreeCommandBuffers(*pDev, CommandPool, 1, &NewCmdBuffer.CmdBuffer); std::cout << "Deleted CommandBuffer.\n"; });
                    return NewCmdBuffer;
                    break;
                }

                default:
                    ThrowError("Attempted to allocate a command buffer with uknown priority");
                    break;
            }
            ThrowError("Attempted to allocate a command buffer with uknown priority, only 0 and 1 are allowed");
        }

        Ek::CommandBuffer AllocateCmdBuffer(int Priority, CommandBufferUsage Usage)
        {
            switch(Priority)
            {
                case 0: 
                {
                    Ek::CommandBuffer NewCmdBuffer(Usage);
                    Allocate(&NewCmdBuffer, 1);
                    CleanupQueue([this, &NewCmdBuffer](){ vkFreeCommandBuffers(*pDev, CommandPool, 1, &NewCmdBuffer.CmdBuffer); std::cout << "Deleted CommandBuffer.\n"; });
                    return NewCmdBuffer;
                    break;
                }

                case 1:
                {
                    Ek::CommandBuffer NewCmdBuffer(Usage);
                    Allocate(&NewCmdBuffer, 1);
                    CleanupQueue([this, &NewCmdBuffer](){ vkFreeCommandBuffers(*pDev, CommandPool, 1, &NewCmdBuffer.CmdBuffer); std::cout << "Deleted CommandBuffer.\n"; });
                    return NewCmdBuffer;
                    break;
                }

                default:
                    ThrowError("Attempted to allocate a command buffer with uknown priority");
                    break;
            }
            ThrowError("Attempted to allocate a command buffer with uknown priority, only 0 and 1 are allowed");
        }

        void SubmitCmdBuffer(Ek::CommandQueue* CommandBuffer, VkQueue SubmitionQueue, VkPipelineStageFlags* WaitStages = nullptr, VkFence* Fence = nullptr, VkSemaphore* WaitSemaphores = nullptr, VkSemaphore* SignalSemaphores = nullptr)

        {
            VkSubmitInfo SubmitInfo{};
            SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            
            if(WaitSemaphores != nullptr)
            {
                SubmitInfo.waitSemaphoreCount = sizeof(WaitSemaphores)/sizeof(WaitSemaphores[0]);
                SubmitInfo.pWaitSemaphores = WaitSemaphores;
            }
            
            if(WaitStages != nullptr)
            {
                SubmitInfo.pWaitDstStageMask = WaitStages;
            }
            
            SubmitInfo.commandBufferCount = 1;
            SubmitInfo.pCommandBuffers = &CommandBuffer->CmdBuffer;
            
            if(SignalSemaphores != nullptr)
            {
                SubmitInfo.signalSemaphoreCount = sizeof(SignalSemaphores)/sizeof(SignalSemaphores[0]);
                SubmitInfo.pSignalSemaphores = SignalSemaphores;
            }

            vkQueueSubmit(SubmitionQueue, 1, &SubmitInfo, *Fence);
        }

        void SubmitCmdBuffer(Ek::CommandBuffer* CommandBuffer, VkQueue SubmitionQueue, VkPipelineStageFlags* WaitStages = nullptr, VkFence* Fence = nullptr, VkSemaphore* WaitSemaphores = nullptr, VkSemaphore* SignalSemaphores = nullptr)
        {
            VkSubmitInfo SubmitInfo{};
            SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
            
            if(WaitSemaphores != nullptr)
            {
                SubmitInfo.waitSemaphoreCount = sizeof(WaitSemaphores)/sizeof(WaitSemaphores[0]);
                SubmitInfo.pWaitSemaphores = WaitSemaphores;
            }
            
            if(WaitStages != nullptr)
            {
                SubmitInfo.pWaitDstStageMask = WaitStages;
            }
            
            SubmitInfo.commandBufferCount = 1;
            SubmitInfo.pCommandBuffers = &CommandBuffer->CmdBuffer;
            
            if(SignalSemaphores != nullptr)
            {
                SubmitInfo.signalSemaphoreCount = sizeof(SignalSemaphores)/sizeof(SignalSemaphores[0]);
                SubmitInfo.pSignalSemaphores = SignalSemaphores;
            }

            vkQueueSubmit(SubmitionQueue, 1, &SubmitInfo, *Fence);
        }

        void Allocate(Ek::CommandBase* Cmd, uint32_t Priority)
        {
            VkCommandBufferAllocateInfo AllocInfo{};
            AllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
            AllocInfo.commandPool = CommandPool;

            switch(Priority)
            {
                case 0:
                    AllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                    break;
                case 1:
                    AllocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
                    break;
                default:
                    AllocInfo.level = VK_COMMAND_BUFFER_LEVEL_SECONDARY;
                    break;
            }

            AllocInfo.commandBufferCount = 1;

            if(vkAllocateCommandBuffers(*pDev, &AllocInfo, &Cmd->CmdBuffer) != VK_SUCCESS)
            {
                ThrowError("Unexpectedly couldn't Allocate Memory for a command buffer, perhaps the pool ran out of space");
            }
        }
    };

}

// Vertices:
namespace Ek
{
    class BasicVertex
    {
        public:
            virtual std::vector<VkVertexInputBindingDescription> GetBindingDescription()
            {}

            virtual std::vector<VkVertexInputAttributeDescription> GetAttributeDescription()
            {}
    };

    class RiggedVertex
    {
        public:
        alignas(16) glm::vec3 Position = glm::vec3(0.0f);
        alignas(16) glm::vec3 Color = glm::vec3(1.0f);
        alignas(16) glm::vec3 Normal = glm::vec3(0.0f);
        alignas(16) ivec3 BoneIDs = {99, 99, 99};
        alignas(16) glm::vec3 BoneWeights = {0, 0, 0};
        uint16_t BoneIDIterator = 0;
        uint16_t BoneWeightIterator = 0;

        void AddBoneID(unsigned int ID)
        {
            if(BoneIDIterator < 3)
            {
                BoneIDs[BoneIDIterator] = ID;
                BoneIDIterator++;
            }
            else
            {
                std::cout << "Error: Too many bone IDs in a vertex" << std::endl;
            }
        }

        void AddBoneWeight(float Weight)
        {
            if(BoneWeightIterator < 3)
            {
                BoneWeights[BoneWeightIterator] = Weight;
                BoneWeightIterator++;
            }
            else
            {
                std::cout << "Error: Too many bone weights in a vertex" << std::endl;
            }
        }

        static std::vector<VkVertexInputBindingDescription> GetBindingDescription()
        {
            std::vector<VkVertexInputBindingDescription> BindingDescription(1);
            BindingDescription[0].binding = 0;
            BindingDescription[0].stride = sizeof(RiggedVertex);
            BindingDescription[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return BindingDescription;
        }

        // IT IS IMPORTANT TO CHANGE THIS WHEN CHANGING THE VERTEX STRUCT OR ADDING ATTRIBUTES
        static std::vector<VkVertexInputAttributeDescription> GetAttributeDescription()
        {
            std::vector<VkVertexInputAttributeDescription> AttributeDescription(5);
            AttributeDescription[0].binding = 0;
            AttributeDescription[0].location = 0;
            AttributeDescription[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            AttributeDescription[0].offset = offsetof(RiggedVertex, Position);

            AttributeDescription[1].binding = 0;
            AttributeDescription[1].location = 1;
            AttributeDescription[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            AttributeDescription[1].offset = offsetof(RiggedVertex, Color);

            AttributeDescription[2].binding = 0;
            AttributeDescription[2].location = 2;
            AttributeDescription[2].format = VK_FORMAT_R32G32B32_SFLOAT;
            AttributeDescription[2].offset = offsetof(RiggedVertex, Normal);

            AttributeDescription[3].binding = 0;
            AttributeDescription[3].location = 3;
            AttributeDescription[3].format = VK_FORMAT_R32G32B32_UINT;
            AttributeDescription[3].offset = offsetof(RiggedVertex, BoneIDs);

            AttributeDescription[4].binding = 0;
            AttributeDescription[4].location = 4;
            AttributeDescription[4].format = VK_FORMAT_R32G32B32_SFLOAT;
            AttributeDescription[4].offset = offsetof(RiggedVertex, BoneWeights);

            return AttributeDescription;
        }
    };

    struct ProcessedRiggedVertex
    {
        alignas(16) glm::vec3 Position;
        alignas(16) glm::vec3 Color;
        alignas(16) glm::vec3 Normal;
        alignas(16) ivec3 BoneIDs;
        alignas(16) glm::vec3 BoneWeights;
    };

    struct ProcessedBasicVertex
    {
        alignas(16) glm::vec3 Position;
        alignas(16) glm::vec3 Color;
        alignas(16) glm::vec3 Normal;
    };
}
