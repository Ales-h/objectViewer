#pragma once

#include "glm/glm.hpp"
#include "material.h"

#include <string>
#include <vector>

namespace fileloader {

struct vertex {
    glm::vec3 p;
    glm::vec3 n;
    glm::vec2 uv;
};

// loads just the vertices and indices to create the mesh (no materials)
void loadObjMesh(std::vector<vertex> &vertices, std::vector<unsigned int> &indices,
                 const std::string &obj_path);

void loadModelFromOBJ(std::vector<vertex> &vertices, std::vector<int> &indices,
                      std::vector<material> &materials, const std::string &obj_path,
                      const std::string &mtl_path);


} // namespace fileloader
