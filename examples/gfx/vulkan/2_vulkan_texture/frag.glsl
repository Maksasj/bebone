#version 450 core

layout (location = 0) in vec3 frag_color;
layout (location = 1) in vec2 tex_cord;

layout (location = 0) out vec4 out_color;

layout(binding = 0) uniform sampler2D textures[];

void main() {
   out_color = vec4(texture(textures[0], tex_cord).rgb, 1.0);
}