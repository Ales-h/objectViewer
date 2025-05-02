#pragma once

#include "glm/glm.hpp"

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


} // namespace fileloader
