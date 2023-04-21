cmake_minimum_required(VERSION 3.25.0)
project("EkWrapper")

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(SDL_image REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Examples)
add_subdirectory(${CMAKE_SOURCE_DIR}/Shaders)
