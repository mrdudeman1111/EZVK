
file(GLOB ExternalResourcesSources ${CMAKE_CURRENT_SOURCE_DIR}/ExternalResources.cpp)

add_executable(ExternalResources ${ExternalResourcesSources})

target_link_libraries(ExternalResources EkWrappers)


file(GLOB ExternalQuerySources ${CMAKE_CURRENT_SOURCE_DIR}/ExtImgQuery.cpp)

add_library(ExtImgQuery ${ExternalQuerySources})

target_link_libraries(ExtImgQuery EkWrappers)


add_compile_definitions(SHADERDIR="${CMAKE_BINARY_DIR}/Shaders/")

file(GLOB ExternalImporterSource ${CMAKE_CURRENT_SOURCE_DIR}/ExternalImporter.cpp)

include_directories("/home/ethanw/Repos/Speed")

add_executable(ExternalImporter ${ExternalImporterSource})

target_link_libraries(ExternalImporter EkWrappers)


add_compile_definitions(TEXPATH="${CMAKE_SOURCE_DIR}/src/Textures")

file(GLOB Render ${CMAKE_CURRENT_SOURCE_DIR}/Render.cpp)

add_executable(Render ${Render})

target_link_libraries(Render EkWrappers)
