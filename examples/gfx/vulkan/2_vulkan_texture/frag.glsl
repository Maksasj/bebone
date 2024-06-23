#version 450 core

layout (location = 0) in vec3 fragColor;
layout (location = 1) in vec2 texCord;

layout (location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D textures[];

void main() {
   outColor = vec4(texture(textures[0], texCord).rgb, 1.0);
}