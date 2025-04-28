#pragma once

#include "glm/glm.hpp"

#include <string>
#include <vector>

namespace fileloader {



// loads just the vertices and indices to create the mesh (no materials, normals etc.)
void loadObjMesh(std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices,
                 const std::string &obj_path);

} // namespace fileloader
