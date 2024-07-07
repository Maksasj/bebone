#version 450 core

layout (location = 0) in vec3 normal;
layout (location = 1) in vec2 texcoord;

layout (location = 0) out vec4 out_color;
layout (location = 1) out vec4 grayscale_color;

void main() {
   out_color = vec4(normal, 1.0);
   grayscale_color = vec4(vec3(out_color.x + out_color.y + out_color.z / 3.0), 1.0);
}