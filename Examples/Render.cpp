#define GLFWAPP
#include <Base/Device.h>

int main()
{
    Ek::Instance Inst;
    Ek::PhysicalDevice PDevice;
    Ek::Device Device;

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

    Ek::Renderpass RP = Device.CreateRenderpass();

    Ek::Window* Window = Device.CreateWindow(&Queues.GraphicsQueues[0]);
    Window->CreateWindow(1920, 1080, "Renderer");
    Window->CreateSurface();

    AllocatedImage InImage = Device.LoadTexture(TEXPATH"Image.jpg");
    InImage.CreateImageView(VK_IMAGE_VIEW_TYPE_2D, VK_IMAGE_ASPECT_COLOR_BIT);
    InImage.CreateRenderTarget(VK_ATTACHMENT_LOAD_OP_LOAD, VK_ATTACHMENT_STORE_OP_STORE, VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

    std::vector<AllocatedImage*> Attachments = {&InImage};

    RP.BuildSubpass(Attachments);

    Ek::Pipeline Pipe = RP.CreatePipeline(1920, 1080);

    std::cout << "Done";
}
