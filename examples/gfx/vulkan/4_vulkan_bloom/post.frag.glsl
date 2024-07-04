#version 450 core

layout (location = 0) in vec3 normal;
layout (location = 1) in vec2 texcoord;

layout (location = 0) out vec4 out_color;

layout(binding = 0) uniform sampler2D textures[];

void main() {
   out_color = vec4(texture(textures[0], texcoord).rgb, 1.0);
}