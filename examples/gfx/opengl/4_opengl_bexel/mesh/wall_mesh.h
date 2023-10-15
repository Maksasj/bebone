#ifndef BEBONE_WALL_MESH_H
#define BEBONE_WALL_MESH_H

#include <vector>

#include "../direction.h"

#include "vertex.h"

namespace bexel {
    template<Direction direction>
    struct WallMesh {
        const vector<Vertex>& get_vertices() const;

        const vector<u32>& get_indices() const {
            static const vector<u32> indices = { 0, 1, 3, 1, 2, 3 };
            return indices;
        }
    };

    template<>
    struct WallMesh<Direction::UP> {
        const vector<Vertex>& get_vertices() const {
            static const vector<Vertex> vertices = {
                {{ 0.5f, 0.5f,  0.5f},  {1.0f, 1.0f, 1.0f}},
                {{-0.5f, 0.5f,  0.5f},  {1.0f, 1.0f, 1.0f}},
                {{-0.5f, 0.5f, -0.5f},  {1.0f, 1.0f, 1.0f}},
                {{ 0.5f, 0.5f, -0.5f},  {1.0f, 1.0f, 1.0f}}
            };

            return vertices;
        }

        const vector<u32>& get_indices() const {
            static const vector<u32> indices = { 0, 1, 3, 1, 2, 3 };
            return indices;
        }
    };

    template<>
    struct WallMesh<Direction::DOWN> {
        const vector<Vertex>& get_vertices() const {
            static const vector<Vertex> vertices = {
                {{ 0.5f, -0.5f,  0.5f},  {1.0f, 1.0f, 1.0f}},
                {{-0.5f, -0.5f,  0.5f},  {1.0f, 1.0f, 1.0f}},
                {{-0.5f, -0.5f, -0.5f},  {1.0f, 1.0f, 1.0f}},
                {{ 0.5f, -0.5f, -0.5f},  {1.0f, 1.0f, 1.0f}}
            };

            return vertices;
        }

        const vector<u32>& get_indices() const {
            static const vector<u32> indices = { 0, 1, 3, 1, 2, 3 };
            return indices;
        }
    };

    template<>
    struct WallMesh<Direction::LEFT> {
        const vector<Vertex>& get_vertices() const {
            static const vector<Vertex> vertices = {
                {{0.5f,  0.5f,  0.5f},  {0.6f, 0.0f, 0.6f}},
                {{0.5f, -0.5f,  0.5f},  {0.6f, 0.0f, 0.6f}},
                {{0.5f, -0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}},
                {{0.5f,  0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}}
            };

            return vertices;
        }

        const vector<u32>& get_indices() const {
            static const vector<u32> indices = { 0, 1, 3, 1, 2, 3 };
            return indices;
        }
    };

    template<>
    struct WallMesh<Direction::RIGHT> {
        const vector<Vertex>& get_vertices() const {
            static const vector<Vertex> vertices = {
                {{-0.5f, -0.5f,  0.5f},  {0.6f, 0.0f, 0.6f}},
                {{-0.5f,  0.5f,  0.5f},  {0.6f, 0.0f, 0.6f}},
                {{-0.5f,  0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}},
                {{-0.5f, -0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}}
            };

            return vertices;
        }

        const vector<u32>& get_indices() const {
            static const vector<u32> indices = { 0, 1, 3, 1, 2, 3 };
            return indices;
        }
    };

    template<>
    struct WallMesh<Direction::FORWARD> {
        const vector<Vertex>& get_vertices() const {
            static const vector<Vertex> vertices = {
                {{ 0.5f, -0.5f, 0.5f},  {0.6f, 0.0f, 0.6f}},
                {{ 0.5f,  0.5f, 0.5f},  {0.6f, 0.0f, 0.6f}},
                {{-0.5f,  0.5f, 0.5f},  {0.6f, 0.0f, 0.6f}},
                {{-0.5f, -0.5f, 0.5f},  {0.6f, 0.0f, 0.6f}}
            };

            return vertices;
        }

        const vector<u32>& get_indices() const {
            static const vector<u32> indices = { 0, 1, 3, 1, 2, 3 };
            return indices;
        }
    };

    template<>
    struct WallMesh<Direction::BACK> {
        const vector<Vertex>& get_vertices() const {
            static const vector<Vertex> vertices = {
                {{ 0.5f,  0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}},
                {{ 0.5f, -0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}},
                {{-0.5f, -0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}},
                {{-0.5f,  0.5f, -0.5f},  {0.6f, 0.0f, 0.6f}}
            };

            return vertices;
        }

        const vector<u32>& get_indices() const {
            static const vector<u32> indices = { 0, 1, 3, 1, 2, 3 };
            return indices;
        }
    };
}

#endif
