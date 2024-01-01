
find_package(Vulkan REQUIRED)

file(GLOB SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Base/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Camera/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Images/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Meshes/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Rendering/*.cpp)

add_compile_definitions(GLFWAPP)

add_library(EkWrappers ${SOURCES})

target_link_libraries(EkWrappers vulkan vulkan-memory-allocator::vulkan-memory-allocator ${glfw3_LIBRARIES} ${glm_LIBRARIES} ${sail_LIBRARIES})

