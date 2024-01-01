#version 450
#pragma shader_stage(vertex)

vec2 Verts[3] = vec2[](
    vec2(0.0, -0.5),
    vec2(0.5, 0.5),
    vec2(-0.5, 0.5)
);

// layout(location = 0)
// layout(location = 1, constant_id = 1) in int BoneSize = ;

layout(location = 0) out vec3 OutColor;

void main()
{
    gl_Position = vec4(Verts[gl_VertexIndex], 0.0, 1.0);
    OutColor = vec3(1.0, 0.0, 0.0);
}