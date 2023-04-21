
find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SDL_image REQUIRED)

file(GLOB SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Base/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Camera/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Images/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Meshes/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Rendering/*.cpp)

file(GLOB SAILSOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/sail/src/*/*.cpp)

add_compile_definitions(GLFWAPP)

add_library(EkWrappers ${SOURCES})

target_link_libraries(EkWrappers vulkan glfw glm)