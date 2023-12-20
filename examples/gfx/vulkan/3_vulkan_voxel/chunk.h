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
            const float v0 = (perlin(x * 0.05f, z * 0.05f) * 0.5f + 0.5f);
            const float v1 = (perlin(x * 0.02f, z * 0.02f) * 0.5f + 0.5f);

            float v = v0 * 16 + v1 * 24;

            if(y < v)
                return false;

            return true;
        }

        void generate(VulkanRenderer& renderer) {
            MeshBuilder builder;

            for(int xCord = 0; xCord < 16; ++xCord) {
                for(int zCord = 0; zCord < 16; ++zCord) {
                    for(int yCord = 0; yCord < 32; ++yCord) {
                        const auto x = static_cast<float>(xCord);
                        const auto y = static_cast<float>(yCord);
                        const auto z = static_cast<float>(zCord);

                        const auto block = get_block_at(x + position.x, y + position.y, z + position.z);

                        if(!block)
                            continue;

                        const auto upBlock =      get_block_at(x + position.x, y + 1 + position.y, z + position.z);
                        const auto downBlock =    get_block_at(x + position.x, y - 1 + position.y, z + position.z);

                        const auto leftBlock =    get_block_at(x + position.x + 1, y + position.y, z + position.z);
                        const auto rightBlock =   get_block_at(x + position.x - 1, y + position.y, z + position.z);
                        
                        const auto forwardBlock = get_block_at(x + position.x, y + position.y, z + 1 + position.z);
                        const auto backBlock =    get_block_at(x + position.x, y + position.y, z - 1 + position.z);

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

        void render(VulkanFrame& frame, VulkanPipelineLayoutImpl& pipelineLayout) {
            VulkanCommandBuffer& cmd = frame.get_command_buffer();

            mesh->bind(cmd);

            transformUBO->set_data(frame, transform);

            cmd.push_constant(pipelineLayout, sizeof(u32), offsetof(Handles, transformHandle), &transformUBO->get_handle(frame.frameIndex).index);
            cmd.draw_indexed(mesh->get_index_count());
        }
};

#endif
