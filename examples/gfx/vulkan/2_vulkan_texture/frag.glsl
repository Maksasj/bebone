#version 450 core

layout (location = 0) in vec3 fragColor;
layout (location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D textures[];

void main() {
   outColor = vec4(fragColor, 1.0);
}