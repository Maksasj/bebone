#include "uv_sphere_mesh_generator.h"

// Implementation from https://gist.github.com/Pikachuxxxx/5c4c490a7d7679824e0e18af42918efc

namespace bebone::renderer {
    using namespace bebone::core;

    UVSphereMeshGenerator::UVSphereMeshGenerator(
        const f32& radius,
        const u32& latitudes,
        const u32& longitudes
    ) : sphere_radius(radius), sphere_latitudes(latitudes), sphere_longitudes(longitudes) {
        recalculate_vertices();
    }

    void UVSphereMeshGenerator::recalculate_vertices() {
        const auto radius_inverse = 1.0f / sphere_radius;
        const auto delta_latitude = BEBONE_PI / sphere_latitudes;
        const auto delta_longitude = 2.0f * BEBONE_PI / sphere_longitudes;

        for (u32 i = 0; i <= sphere_latitudes; ++i) {
            const auto latitude_angle = BEBONE_PI / 2 - i * delta_latitude;
            f32 xy = sphere_radius * cosf(latitude_angle);
            f32 z = sphere_radius * sinf(latitude_angle);

            for (u32 j = 0; j <= sphere_longitudes; ++j) {
                const auto longitude_angle = j * delta_longitude;

                auto position = Vec3f { xy * cosf(longitude_angle), xy * sinf(longitude_angle), z };
                sphere_vertices.push_back(position);

                auto texcoord = Vec2f { (f32)j/ sphere_longitudes, (f32)i/ sphere_latitudes };
                sphere_texcoord.push_back(texcoord);

                auto normal = position * radius_inverse;
                sphere_normals.push_back(normal);
            }
        }

        for(int i = 0; i < sphere_latitudes; ++i) {
            u32 k1 = i * (sphere_longitudes + 1);
            u32 k2 = k1 + sphere_longitudes + 1;

            for(int j = 0; j < sphere_longitudes; ++j, ++k1, ++k2) {
                if (i != 0) {
                    sphere_indices.push_back(k1);
                    sphere_indices.push_back(k2);
                    sphere_indices.push_back(k1 + 1);

                    // sphere_indices.push_back(k1);
                    // sphere_indices.push_back(k1 + 1);
                    // sphere_indices.push_back(k2);
                }

                if (i != (sphere_latitudes - 1)) {
                    sphere_indices.push_back(k1 + 1);
                    sphere_indices.push_back(k2);
                    sphere_indices.push_back(k2 + 1);

                    // sphere_indices.push_back(k1 + 1);
                    // sphere_indices.push_back(k2 + 1);
                    // sphere_indices.push_back(k2);
                }
            }
        }
    }

    void UVSphereMeshGenerator::set_radius(const f32& radius) {
        sphere_radius = radius;
    }

    void UVSphereMeshGenerator::set_latitudes(const u32& latitudes) {
        sphere_latitudes = latitudes;

        if(sphere_latitudes < 2)
            sphere_latitudes = 2;
    }

    void UVSphereMeshGenerator::set_longitudes(const u32& longitudes) {
        sphere_longitudes = longitudes;

        if(sphere_longitudes < 3)
            sphere_longitudes = 3;
    }


    f32 UVSphereMeshGenerator::get_radius() const {
        return sphere_radius;
    }

    u32 UVSphereMeshGenerator::get_latitudes() const {
        return sphere_latitudes;
    }

    u32 UVSphereMeshGenerator::get_longitudes() const {
        return sphere_longitudes;
    }

    void UVSphereMeshGenerator::append_vertices(const std::shared_ptr<IMeshBuilder>& builder) {
        auto vertices = std::vector<Vertex> {};

        for(int i = 0; i < sphere_vertices.size(); ++i) {
            vertices.push_back({sphere_vertices[i], sphere_normals[i], sphere_texcoord[i]});
        }

        builder->append_raw(vertices.data(), vertices.size(), sphere_indices.data(), sphere_indices.size());
    }

    std::shared_ptr<IMeshImpl> UVSphereMeshGenerator::generate(const std::shared_ptr<IMeshBuilder>& builder) {
        append_vertices(builder);
        return builder->build();
    }
}
