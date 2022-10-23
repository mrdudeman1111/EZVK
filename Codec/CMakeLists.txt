CMAKE_MINIMUM_REQUIRED(VERSION 3.22.0)
project(VulkanEncoder)

add_executable(VulkanEncoder ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(VulkanEncoder Vulkan::Vulkan)
