#version 450 core

layout (location = 0) in vec3 normal;
layout (location = 1) in vec2 texcoord;

layout (location = 0) out vec4 out_color;

layout(set = 0, binding = 2) uniform sampler2D textures[];

void main() {
   vec4 result = vec4(0.0f);

   for(int x = -5; x < 5; ++x) {
      for(int y = -5; y < 5; ++y) {
         vec2 offset = 5*vec2(x / 800.0, y / 600.0);
         result += texture(textures[0], texcoord + offset);
      }
   }

   out_color = result * (1.0/50.0);
}