#pragma once

#include <string>

#include "glm/glm.hpp"

class material {
  private:
    std::string name;
    glm::vec3 m_albedo = glm::vec3(1.0f);
    float m_shininess = 32.0f;
    unsigned int m_albedoMap = 0;
    unsigned int m_normalMap = 0;
    bool m_alphaBlend = false;
  public:
    void apply() const;
};
