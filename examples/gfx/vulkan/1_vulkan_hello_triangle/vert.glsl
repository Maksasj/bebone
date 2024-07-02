#version 450 core
#extension GL_EXT_nonuniform_qualifier : enable

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

layout (location = 0) out vec3 frag_color;

void main() {
    gl_Position = vec4(position, 1.0);

    frag_color = color;
}
