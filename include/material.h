#pragma once

#include <string>

#include "GLprogram.h"
#include "glm/glm.hpp"

class material {
  public:
    std::string name;
    glm::vec3 m_ambient = glm::vec3(1.0f);
    glm::vec3 m_diffuse = glm::vec3(1.0f);
    glm::vec3 m_specular = glm::vec3(1.0f);
    float m_shininess = 32.0f;
    unsigned int m_ambientMap = 0;
    unsigned int m_diffuseMap = 0;
    unsigned int m_specularMap = 0;
    unsigned int m_normalMap = 0;

  public:
    void apply(GLprogram& program) const{
        program.setUniform3f("material.ambient", m_ambient.x, m_ambient.y, m_ambient.z);
        program.setUniform3f("material.diffuse", m_diffuse.x, m_diffuse.y, m_diffuse.z);
        program.setUniform3f("material.specular", m_specular.x, m_specular.y,
                             m_specular.z);
        program.setUniform1f("material.shininess", m_shininess);
    }
};
