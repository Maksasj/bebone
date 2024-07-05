#version 450 core
#extension GL_EXT_nonuniform_qualifier : enable

layout (location = 0) in vec3 normal;
layout (location = 1) in vec2 texcoord;

layout (location = 0) out vec4 out_color;

layout( push_constant ) uniform Handles {
   int geometry_texture;
   int blur_texture;
} handles;

layout(binding = 0) uniform sampler2D textures[];

void main() {
   vec4 fragment = texture(textures[handles.geometry_texture], texcoord);
   vec4 bloom = texture(textures[handles.blur_texture], texcoord);

   vec4 color = fragment + bloom;

   float exposure = 0.8f;
   vec4 toneMapped = vec4(1.0) - exp(-color * exposure);

   float gamma = 1.0f;

   out_color = pow(toneMapped, vec4(1.0f / gamma));
}