#version 450 core

layout (location = 0) in vec3 normal;
layout (location = 1) in vec2 texcoord;

layout (location = 0) out vec4 out_color;

layout(binding = 0) uniform sampler2D textures[];

vec2 screen_size = vec2(800, 600);

void main() {
   vec4 result = vec4(0.0f);

   for(int x = -25; x < 25; ++x) {
      for(int y = -25; y < 25; ++y) {
         vec2 offset = vec2(x/screen_size.x, y/screen_size.y);
         result += texture(textures[0], texcoord + offset);
      }
   }

   out_color = result * (1.0/2500.0);
}