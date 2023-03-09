// #pragma once

#include <Rendering/EkPipeline.hpp>
#include <Base/EkWindow.hpp>

// enum QueueType
// {
//     Graphics = 1,
//     Compute = 2,
//     Transfer = 4,
//     SparseBind = 8,
//     Protected = 16,
//     OpticFlow = 32
//     #ifdef VK_ENABLE_BETA_EXTENSIONS
//     ,
//     Decode = 64,
//     Encode = 128
//     #endif
// };

// typedef std::map<QueueType, int> QueueList;

// namespace Mesh
// {
//     // glm::mat4 ConvertMat4(aiMatrix4x4 AssimpMatrix);
// }

// struct EkQueue
// {
//     VkQueue VulkanQueue;
//     bool Used;
// };

// struct QueueFamilyIndices
// {
//     uint32_t GraphicsFamily = -1;
//     uint32_t ComputeFamily = -1;
//     uint32_t TransferFamily = -1;
//     uint32_t SparseBindingFamily = -1;
//     uint32_t ProtectedFamily = -1;
//     uint32_t OpticFlowFamily = -1;

//     #ifdef VK_ENABLE_BETA_EXTENSIONS
//         // Provided by VK_KHR_video_decode_queue
//         uint32_t DecodeFamily = -1;
//         // Provided by VK_KHR_video_encode_queue
//         uint32_t EncodeFamily = -1;
//     #endif
// };
