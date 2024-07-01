#version 450 core
#extension GL_EXT_nonuniform_qualifier : enable

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

layout (location = 0) out vec3 out_normal;
layout (location = 1) out vec2 out_texcoord;

layout(binding = 0) uniform TransformUBO {
    mat4 transform;
} transform[];

layout(binding = 1) uniform CameraUBO {
    mat4 cam;
} camera[];

layout( push_constant ) uniform Handles {
    int camera;
    int transform;
} handles;

void main() {
    gl_Position = camera[handles.camera].cam * transform[handles.transform].transform * vec4(position, 1.0);

    out_normal = normal;
    out_texcoord = texcoord;
}
