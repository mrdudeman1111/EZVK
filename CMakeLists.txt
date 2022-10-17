cmake_minimum_required(VERSION 3.23.0)
project("Vulkan Wrapper")

file(GLOB SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
    # ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include /usr/include)

add_library(VkWrapper ${SRC})
add_executable(VkTester ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_compile_definitions(GLFWAPP)

target_link_libraries(VkWrapper Vulkan::Vulkan glfw VulkanMemoryAllocator glm)
target_link_libraries(VkTester VkWrapper Vulkan::Vulkan glfw VulkanMemoryAllocator glm)

