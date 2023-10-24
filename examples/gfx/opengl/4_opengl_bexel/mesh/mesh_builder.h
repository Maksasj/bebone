#ifndef BEXEL_MESH_BUILDER_H
#define BEXEL_MESH_BUILDER_H

#include <memory>

#include "mesh.h"
#include "vertex.h"

#include "../transform.h"

namespace bexel {
    class MeshBuilder {
        private:
            vector<Vertex> m_vertices;
            vector<u32> m_indices;

            u32 m_indexOffset;

        public:
            MeshBuilder();

            template<class _MeshData>
            MeshBuilder& append(const _MeshData& meshData, const Transform& transform) {
                for(auto vertex : meshData.get_vertices()) {
                    vertex.rotate(transform.rotation);
                    vertex.translate(transform.translation);
                    vertex.scale(transform.scale);

                    m_vertices.push_back(vertex);
                }

                u32 maxIndex = 0;
                for(const auto& index : meshData.get_indices()) {
                    m_indices.push_back(index + m_indexOffset);

                    if(index > maxIndex)
                        maxIndex = index;
                }

                m_indexOffset += maxIndex + 1;

                return *this;
            }

            template<class _MeshData>
            MeshBuilder& append(const _MeshData& meshData, const vector<Vec2f>& textureCoords, const Transform& transform) {
                const auto size = meshData.get_vertices().size();
                const auto& vertices = meshData.get_vertices();

                for(size_t i = 0; i < size; ++i) {
                    auto vertex = vertices[i];

                    vertex.rotate(transform.rotation);
                    vertex.translate(transform.translation);
                    vertex.scale(transform.scale);

                    vertex.tex = textureCoords[i];

                    m_vertices.push_back(vertex);
                }

                u32 maxIndex = 0;
                for(const auto& index : meshData.get_indices()) {
                    m_indices.push_back(index + m_indexOffset);

                    if(index > maxIndex)
                        maxIndex = index;
                }

                m_indexOffset += maxIndex + 1;

                return *this;
            }

            unique_ptr<Mesh> build();
    };
}

#endif
