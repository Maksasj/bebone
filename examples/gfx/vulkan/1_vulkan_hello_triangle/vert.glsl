#version 450 core
#extension GL_EXT_nonuniform_qualifier : enable

layout (location = 0) in vec3 position;

void main() {
    gl_Position = vec4(position, 1.0);
}
