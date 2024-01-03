# EZVK
***

This is the second project I made while learning vulkan, my previous project followed the (wonderful) guides found at [vkguide.dev](https://vkguide.dev) and [vulkan-tutorial](https://vulkan-tutorial.com).
But with this project I decided to take different approach to vulkan, and decided to start *abstracting* different parts of vulkan, such as Instance creation, Device creation, layer and extension management, command buffers, renderpasses and subpasses, window creation and presentation, framebuffer assembly, and a couple of more smaller topics. For now I have shelved the project, but I plan on coming back to it once I've learned more about rendering architecture and performant rendering models and abstractions. My current project is at [Quick Render](https://github.com/mrdudeman1111/QuickRender)

All this project does is abstract and wrap the vulkan api into helpful classes and structures for quicker implementation.

# Building
***

Assuming that you have installed and configured conan, you can run this in the build folder to compile this project:

> conan install ../ --build=missing
>
> cmake ../ --preset conan-release

