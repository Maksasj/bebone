#version 450 core

layout (location = 0) in vec3 fragColor;
layout (location = 1) in vec2 fragTexCoord;
layout (location = 2) flat in int norm;

layout (location = 0) out vec4 outColor;

void main() {
   vec4 color = vec4(fragColor, 1.0);

   if(norm == 0) {
      color *= 1.0;
   } else if(norm == 1) {
      color *= 0.8;
   } else if(norm == 2) {
      color *= 0.6;
   }

   outColor = color;
}