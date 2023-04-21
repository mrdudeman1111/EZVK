file(GLOB Shaders ${CMAKE_CURRENT_SOURCE_DIR}/*.glsl)

add_compile_definitions(SHADERDIR)

foreach(Shader ${Shaders})

    get_filename_component(FileName ${Shader} NAME)
    execute_process(
        COMMAND bash -c " glslc -c ${Shader} -o ${CMAKE_CURRENT_BINARY_DIR}/${FileName}.spv"
    )
    
endforeach(Shader ${Shaders})
