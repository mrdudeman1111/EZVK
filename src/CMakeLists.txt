CMAKE_MINIMUM_REQUIRED(VERSION 3.18.1)
project("Example Vr App")

file(GLOB SOURCES .cpp)

add_executable(VrApp ${SOURCES})
