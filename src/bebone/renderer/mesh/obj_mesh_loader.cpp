#include "obj_mesh_loader.h"

namespace bebone::renderer {

    OBJMeshLoader::OBJMeshLoader(const std::shared_ptr<IMeshBuilder<Vertex>>& builder) : IMeshLoader(builder) {

    }

    // Todo, Move this
    std::vector<string> split(const std::string& s, const std::string& delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        std::string token;
        std::vector<string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            token = s.substr (pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back (token);
        }

        res.push_back (s.substr (pos_start));

        return res;
    }

    void OBJMeshLoader::reset() {
        builder->reset();
    }

    std::shared_ptr<IMesh> OBJMeshLoader::load_from_file(const std::string& file_path) {
        auto file = std::ifstream(file_path);

        auto raw_vertices = std::vector<Vec3f> {};
        auto raw_normals = std::vector<Vec3f> {};
        auto raw_texcoord = std::vector<Vec2f> {};

        auto vertices = std::vector<Vertex> {};
        auto indicies = std::vector<u32> {};

        u32 index = 0;
        auto corrected_index =  std::unordered_map<string, u32> {};

        string line;
        while(std::getline(file, line)) {
            std::stringstream data(line);

            string keyword;
            data >> keyword;

            if(keyword == "v") {
                f32 x, y, z;
                data >> x >> y >> z;
                raw_vertices.emplace_back(x, y, z);
            } else if(keyword == "vt") {
                f32 x, y;
                data >> x >> y;
                raw_texcoord.emplace_back(x, y);
            } else if(keyword == "vn") {
                f32 x, y, z;
                data >> x >> y >> z;
                raw_normals.emplace_back(x, y, z);
            } else if(keyword == "f") {
                std::string in[3];
                data >> in[0] >> in[1] >> in[2];

                for(int o = 0; o < 3; ++o) {
                    auto i = in[o];
                    auto v = split(i, "/");

                    if(!corrected_index.contains(v[0])) {
                        corrected_index.insert(make_pair(v[0], index));

                        auto vertex = raw_vertices[stoi(v[0]) - 1];

                        auto normal = Vec3f::zero;
                        if(v.size() >= 3 && !v[2].empty())
                            normal = raw_normals[stoi(v[2]) - 1];

                        const static Vec2f rep_texcoord[] = {
                            {0.0f, 0.0f},
                            {0.0f, 1.0f},
                            {1.0f, 0.0f}
                        };

                        auto texcoord = rep_texcoord[o];

                        if(v.size() >= 3 && !v[1].empty())
                            texcoord = raw_texcoord[stoi(v[1]) - 1];

                        vertices.push_back(Vertex{vertex, normal, texcoord});
                        ++index;
                    }

                    indicies.push_back(corrected_index[v[0]]);
                }
            }
        }

        builder->append_raw(vertices.data(), vertices.size(), indicies.data(), indicies.size());

        return builder->build();
    }
}
