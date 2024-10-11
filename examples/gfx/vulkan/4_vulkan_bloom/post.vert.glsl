#version 450 core
#extension GL_EXT_nonuniform_qualifier : enable

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

layout (location = 0) out vec3 out_normal;
layout (location = 1) out vec2 out_texcoord;

void main() {
    gl_Position = vec4(position, 1.0);

    out_normal = normal;
    out_texcoord = texcoord;
}
