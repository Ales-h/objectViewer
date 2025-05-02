#include "fileloader.h"
#include "tiny_obj_loader.h"

#include <cstdlib>
#include <iostream>

namespace fileloader {

void loadVertices(const std::vector<float> &positions, const std::vector<float> &norm,
                  const std::vector<float> &uvs, std::vector<vertex> &vertices) {
    size_t vertices_count = positions.size() / 3;
    std::cout << "positions count: " << positions.size() / 3 << '\n';
    std::cout << "normals count: " << norm.size() / 3 << '\n';

    glm::vec3 normal = glm::vec3{0, 0, 0};
    glm::vec2 uv = glm::vec2{0, 0};
    for (int i = 0; i < vertices_count; i++) {
        glm::vec3 pos =
            glm::vec3{positions[i * 3], positions[i * 3 + 1], positions[i * 3 + 2]};
        if (norm.size() >= 3 * (i + 1)) {
            normal = glm::vec3{norm[i * 3], norm[i * 3 + 1], norm[i * 3 + 2]};
        }
        if (uvs.size() >= 2 * (i + 1)) {
            uv = glm::vec2{uvs[i * 2], uvs[i * 2 + 1]};
        }
        vertices.emplace_back(vertex{pos, normal, uv});
    }
}

void loadObjMesh(std::vector<vertex> &vertices, std::vector<unsigned int> &indices,
                 const std::string &obj_path) {

    // loading the model
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning, err;

    bool success = tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &err,
                                    obj_path.c_str(), nullptr);
    if (!err.empty()) {
        std::cerr << err << "\n";
    }
    if (!success) {
        std::cerr << "model loading failed! in loadObjMesh()\n";
        std::exit(-1);
    }

    auto pos = attrib.vertices;
    auto norm = attrib.normals;
    auto uvs = attrib.texcoords;
    // loading vertices
    for (auto shape : shapes) {
        auto mesh = shape.mesh;
        for (auto idx : mesh.indices) {
            int p_idx = idx.vertex_index * 3;
            int n_idx = idx.normal_index * 3;
            int uv_idx = idx.texcoord_index * 2;
            glm::vec3 p = glm::vec3(pos[p_idx], pos[p_idx + 1], pos[p_idx + 2]);
            glm::vec3 n = glm::vec3(0, 0, 0);
            if (norm.size() > n_idx) {
                n = glm::vec3(norm[n_idx], norm[n_idx + 1], norm[n_idx + 2]);
            }
            glm::vec2 uv = glm::vec2(0, 0);
            if (uvs.size() > uv_idx) {
                uv = glm::vec2(uvs[uv_idx], uvs[uv_idx + 1]);
            }
            vertices.push_back(vertex{p, n, uv});
        }
    }
}

} // namespace fileloader
