#ifndef BEXEL_MESH_BUILDER_H
#define BEXEL_MESH_BUILDER_H

#include <memory>

#include "mesh.h"
#include "vertex.h"

#include "../transform.h"

namespace bexel {
    class MeshBuilder {
        private:
            vector<Vertex> vertices;
            vector<u32> indices;

            u32 index_offset;

        public:
            MeshBuilder();

            template<class MeshData>
            MeshBuilder& append(const MeshData& mesh_data, const Transform& transform) {
                for(auto vertex : mesh_data.get_vertices()) {
                    vertex.rotate(transform.rotation);
                    vertex.translate(transform.translation);
                    vertex.scale(transform.scale);

                    vertices.push_back(vertex);
                }

                u32 max_index = 0;
                for(const auto& index : mesh_data.get_indices()) {
                    indices.push_back(index + index_offset);

                    if(index > max_index)
                        max_index = index;
                }

                index_offset += max_index + 1;

                return *this;
            }

            template<class MeshData>
            MeshBuilder& append(const MeshData& mesh_data, const vector<Vec2f>& texture_coords, const Transform& transform) {
                const auto size = mesh_data.get_vertices().size();
                const auto& mesh_vertices = mesh_data.get_vertices();

                for(size_t i = 0; i < size; ++i) {
                    auto vertex = mesh_vertices[i];

                    vertex.rotate(transform.rotation);
                    vertex.translate(transform.translation);
                    vertex.scale(transform.scale);

                    vertex.tex = texture_coords[i];

                    vertices.push_back(vertex);
                }

                u32 max_index = 0;
                for(const auto& index : mesh_data.get_indices()) {
                    indices.push_back(index + index_offset);

                    if(index > max_index)
                        max_index = index;
                }

                index_offset += max_index + 1;

                return *this;
            }

            unique_ptr<Mesh> build();
    };
}

#endif
