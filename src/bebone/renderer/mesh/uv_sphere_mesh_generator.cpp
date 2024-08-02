#include "uv_sphere_mesh_generator.h"

#define BEBONE_PI 3.14159265359f

namespace bebone::renderer {
    using namespace bebone::core;

    UVSphereMeshGenerator::UVSphereMeshGenerator(
        const f32& radius,
        const u32& latitudes,
        const u32& longitudes
    ) : radius(radius), latitudes(latitudes), longitudes(longitudes) {
        generate_sphere_smooth();
    }

    void UVSphereMeshGenerator::generate_sphere_smooth() {
        if(longitudes < 3)
            longitudes = 3;
        if(latitudes < 2)
            latitudes = 2;

        std::vector<Vec3f> vertices;
        std::vector<Vec3f> normals;
        std::vector<Vec2f> uv;
        std::vector<unsigned int> indices;

        float nx, ny, nz, lengthInv = 1.0f / radius;    // normal
        // Temporary vertex
        struct ThisVertex
        {
            float x, y, z, s, t; // Postion and Texcoords
        };

        float deltaLatitude = BEBONE_PI / latitudes;
        float deltaLongitude = 2 * BEBONE_PI / longitudes;
        float latitudeAngle;
        float longitudeAngle;

        // Compute all vertices first except normals
        for (int i = 0; i <= latitudes; ++i)
        {
            latitudeAngle = BEBONE_PI / 2 - i * deltaLatitude; /* Starting -pi/2 to pi/2 */
            float xy = radius * cosf(latitudeAngle);    /* r * cos(phi) */
            float z = radius * sinf(latitudeAngle);     /* r * sin(phi )*/

            /*
             * We add (latitudes + 1) vertices per longitude because of equator,
             * the North pole and South pole are not counted here, as they overlap.
             * The first and last vertices have same position and normal, but
             * different tex coords.
             */
            for (int j = 0; j <= longitudes; ++j)
            {
                longitudeAngle = j * deltaLongitude;

                ThisVertex vertex;
                vertex.x = xy * cosf(longitudeAngle);       /* x = r * cos(phi) * cos(theta)  */
                vertex.y = xy * sinf(longitudeAngle);       /* y = r * cos(phi) * sin(theta) */
                vertex.z = z;                               /* z = r * sin(phi) */
                vertex.s = (float)j/longitudes;             /* s */
                vertex.t = (float)i/latitudes;              /* t */
                vertices.push_back(Vec3f(vertex.x, vertex.y, vertex.z));
                uv.push_back(Vec2f(vertex.s, vertex.t));

                // normalized vertex normal
                nx = vertex.x * lengthInv;
                ny = vertex.y * lengthInv;
                nz = vertex.z * lengthInv;
                normals.push_back(Vec3f(nx, ny, nz));
            }
        }

        unsigned int k1, k2;
        for(int i = 0; i < latitudes; ++i) {
            k1 = i * (longitudes + 1);
            k2 = k1 + longitudes + 1;
            // 2 Triangles per latitude block excluding the first and last longitudes blocks
            for(int j = 0; j < longitudes; ++j, ++k1, ++k2) {
                if (i != 0) {
                    indices.push_back(k1);
                    indices.push_back(k2);
                    indices.push_back(k1 + 1);

                    // indices.push_back(k1);
                    // indices.push_back(k1 + 1);
                    // indices.push_back(k2);
                }

                if (i != (latitudes - 1)) {
                    indices.push_back(k1 + 1);
                    indices.push_back(k2);
                    indices.push_back(k2 + 1);

                    // indices.push_back(k1 + 1);
                    // indices.push_back(k2 + 1);
                    // indices.push_back(k2);
                }
            }
        }

        sphereVertices = vertices;
        sphereNormals = normals;
        sphereUVs = uv;
        sphereIndices = indices;
    }

    void UVSphereMeshGenerator::append_vertices(const std::shared_ptr<IMeshBuilder>& builder) {
        auto vertices = std::vector<Vertex> {};

        for(int i = 0; i < sphereVertices.size(); ++i) {
            vertices.push_back({sphereVertices[i], sphereNormals[i], sphereUVs[i]});
        }

        builder->append_raw(vertices.data(), vertices.size(), sphereIndices.data(), sphereIndices.size());
    }

    std::shared_ptr<IMesh> UVSphereMeshGenerator::generate(const std::shared_ptr<IMeshBuilder>& builder) {
        append_vertices(builder);
        return builder->build();
    }
}
