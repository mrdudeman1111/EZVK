cmake_minimum_required(VERSION 3.25.0)
project("EkWrapper")

file(GLOB SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Base/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Camera/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Images/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Meshes/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Rendering/*.cpp)

file(GLOB TSTSRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/ ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_compile_definitions()

add_library(EkWrappers ${SOURCE})
add_executable(test ${TSTSRC})

target_link_libraries(test PUBLIC EkWrappers)
