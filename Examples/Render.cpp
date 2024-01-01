#define GLFWAPP
#include <Base/Device.h>

// Figure what needs to be passed to renderpass and what needs to be passed to pipeline/material/shader

// class OurVertex : Ek::BasicVertex
// {
//     public:
//     glm::vec3 Position;

//     virtual std::vector<VkVertexInputAttributeDescription> GetAttributeDescription()
//     {
//         std::vector<VkVertexInputAttributeDescription> Ret(1);

//         Ret[0].binding = 0;
//         Ret[0].location = 0;

//         // Format is just a way to specify byte size of each element.
//         Ret[0].format = VK_FORMAT_R32G32B32_SFLOAT;

//         Ret[0].offset = offsetof(OurVertex, Position);

//         return Ret;
//     }

//     virtual std::vector<VkVertexInputBindingDescription> GetBindingDescription()
//     {
//         std::vector<VkVertexInputBindingDescription> Ret(1);
//         Ret[0].binding = 0;
//         Ret[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
//         Ret[0].stride = sizeof(OurVertex);
//     }
// };

int main()
{
    Ek::Instance Inst;
    Ek::PhysicalDevice PDevice;
    Ek::Device Device;

    Inst.RequestLayer("VK_LAYER_KHRONOS_validation");
    Inst.CreateInstance(VK_API_VERSION_1_2, "Quick Render");

    PDevice.PickPhysDev(&Inst);
    Device = PDevice.GetLogicalDevice();

    QueueList List;
    List[QueueType::Graphics] = 1;
    List[QueueType::Compute] = 0;
    List[QueueType::OpticFlow] = 0;
    List[QueueType::Protected] = 0;
    List[QueueType::SparseBind] = 0;
    List[QueueType::Transfer] = 0;

    Ek::Queues Queues;

    Device.Create(&Inst, &List, &Queues);

    Ek::Window* Window = Device.CreateWindow(&Queues.GraphicsQueues[0]);
    Window->CreateWindow(1920, 1080, "Renderer");
    Window->CreateSurface();

    AllocatedImage InImage = Device.LoadTexture(TEXPATH"Image.jpg");
    InImage.CreateImageView(VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT);
    InImage.BuildAttachmentInformation(VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE, VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
    InImage.Type = RtColor;

    Window->CreateSwapchain(2);

    Ek::Renderpass RP = Device.CreateRenderpass();

    RP.BuildSubpass();

    RP.PushAttachment(&Window->FrameBuffers[0]->ImageBuffer, 0);
    RP.PushAttachment(&Window->FrameBuffers[0]->DepthBuffer, 0);
    RP.PushAttachment(&InImage, 0);

    Ek::Pipeline Pipe = RP.CreatePipeline(1920, 1080);

    RP.Build(Window);

    Ek::Shader Vert = Device.CreateShader(SHADERDIR"ImgVert.glsl.spv");
    Vert.ShaderEntryPoint = "main";
    Vert.Type = Ek::eShaderVert;
    Vert.Stage = VK_SHADER_STAGE_VERTEX_BIT;

    Ek::Shader Frag = Device.CreateShader(SHADERDIR"ImgFrag.glsl.spv");
    Frag.ShaderEntryPoint = "main";
    Frag.Type = Ek::eShaderFrag;
    Frag.Stage = VK_SHADER_STAGE_FRAGMENT_BIT;

    Ek::Material Mat = Device.CreateMaterial();
    Mat.AddShader(&Vert);
    Mat.AddShader(&Frag);
    Mat.AddShaderInput(Ek::eShaderFrag, 0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, &InImage, 1);
    Mat.Build(nullptr);

    Pipe.Build(&Mat, 0, nullptr);

    std::cout << "Done\n";

    Window->~Window();
    Device.~Device();
    Inst.~Instance();
}
