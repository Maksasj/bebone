#ifndef CHUNK_H
#define CHUNK_H

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

#include "handles.h"
#include "transform.h"
#include "mesh.h"
#include "mesh_builder.h"
#include "noise.h"

using namespace bebone::gfx;
using namespace bebone::core;

class Chunk {
    private:
        std::unique_ptr<Mesh> mesh;
        
        Transform transform;
        Vec3f position;

        std::unique_ptr<UniformBuffer<Transform>> transformUBO;

    public:

        Chunk(GPUResourceManager& resourceManager, GPUResourceSet& resourceSet, const Vec3f& pos) {
            transformUBO = std::make_unique<UniformBuffer<Transform>>(resourceManager.create_uniform_buffer_impl<Transform>(resourceSet, 0));
        
            position = pos;

            transform = Transform{
                Mat4f::translation(position),
                Mat4f::scale(1.0f),
                Mat4f::identity()
            };
        }

        static bool get_block_at(float x, float y, float z) {
            // float v = sin(x * 0.5f) * 0.5f + 0.5f;
            float v = perlin(x * 0.05f, z * 0.05f) * 0.5f + 0.5f;
            v *= 16;

            if(y < v)
                return false;

            return true;
        }

        void generate(VulkanRenderer& renderer) {
            MeshBuilder builder;

            for(int x = 0; x < 16; ++x) {
                for(int z = 0; z < 16; ++z) {
                    for(int y = 0; y < 16; ++y) {
                        bool block = get_block_at(x + position.x, y + position.y, z + position.z);

                        if(block == false)
                            continue;

                        bool upBlock =      get_block_at(x + position.x, y + 1 + position.y, z + position.z);
                        bool downBlock =    get_block_at(x + position.x, y - 1 + position.y, z + position.z);

                        bool leftBlock =    get_block_at(x + position.x + 1, y + position.y, z + position.z);
                        bool rightBlock =   get_block_at(x + position.x - 1, y + position.y, z + position.z);
                        
                        bool forwardBlock = get_block_at(x + position.x, y + position.y, z + 1 + position.z);
                        bool backBlock =    get_block_at(x + position.x, y + position.y, z - 1 + position.z);

                        if(!upBlock)        builder.append(QUAD_MESH_UP_VERTEX_DATA, QUAD_MESH_INDICES_DATA, Vec3f(x, y, z));
                        if(!downBlock)      builder.append(QUAD_MESH_DOWN_VERTEX_DATA, QUAD_MESH_INDICES_DATA, Vec3f(x, y, z));
                        if(!leftBlock)      builder.append(QUAD_MESH_LEFT_VERTEX_DATA, QUAD_MESH_INDICES_DATA, Vec3f(x, y, z));
                        if(!rightBlock)     builder.append(QUAD_MESH_RIGHT_VERTEX_DATA, QUAD_MESH_INDICES_DATA, Vec3f(x, y, z));
                        if(!forwardBlock)   builder.append(QUAD_MESH_FORWARD_VERTEX_DATA, QUAD_MESH_INDICES_DATA, Vec3f(x, y, z));
                        if(!backBlock)      builder.append(QUAD_MESH_BACK_VERTEX_DATA, QUAD_MESH_INDICES_DATA, Vec3f(x, y, z));
                    }
                }
            }

            mesh = builder.build(renderer);
        }

        void render(VulkanFrame& frame, PipelineLayout& pipelineLayout) {
            VulkanCommandBuffer& cmd = frame.get_command_buffer();

            mesh->bind(cmd);

            transformUBO->set_data(frame, transform);

            cmd.push_constant(pipelineLayout, sizeof(u32), offsetof(Handles, transformHandle), &transformUBO->get_handle(frame.frameIndex).index);
            cmd.draw_indexed(mesh->get_index_count());
        }
};

#endif
