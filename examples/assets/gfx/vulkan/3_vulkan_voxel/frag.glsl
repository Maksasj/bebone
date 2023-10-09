#version 450 core

layout (location = 0) in vec3 fragColor;
layout (location = 0) out vec4 outColor;

void main() {
   vec4 color = vec4(fragColor, 1.0);

   outColor = color;
}