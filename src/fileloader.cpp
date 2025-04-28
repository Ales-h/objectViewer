#include "fileloader.h"
#include "tiny_obj_loader.h"

#include <cstdlib>
#include <iostream>

namespace fileloader {

void verticesToVec3(const std::vector<float>& data,
                        std::vector<glm::vec3> &vertices) {

    for (int i = 0; i < data.size(); i += 3) {
        vertices.emplace_back(glm::vec3{data[i], data[i + 1],
                                        data[i + 2]});
    }
}

void loadObjMesh(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices,
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

    // loading vertices
    verticesToVec3(attrib.vertices, vertices);
    for (int i = 0; i < attrib.vertices.size(); i += 3) {
        vertices.emplace_back(glm::vec3{attrib.vertices[i], attrib.vertices[i + 1],
                                        attrib.vertices[i + 2]});
    }

    tinyobj::shape_t shape = shapes[0];
    auto data = shape.mesh.indices;

    for (int i = 0; i < data.size(); i++) {
        indices.emplace_back(data[i].vertex_index);
    }
}

} // namespace fileloader
