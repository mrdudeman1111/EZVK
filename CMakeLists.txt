cmake_minimum_required(VERSION 3.25.0)
project("EkWrapper")

find_package(Vulkan REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(stb CONFIG REQUIRED)
find_package(vulkan-memory-allocator CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include ${glm_INCLUDE_DIRS} ${glfw3_INCLUDE_DIRS} ${stb_INCLUDE_DIRS})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Examples)
add_subdirectory(${CMAKE_SOURCE_DIR}/Shaders)
