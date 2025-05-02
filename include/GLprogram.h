#pragma once
#include "glm/glm.hpp"

#include <string>
#include <unordered_map>

class GLprogram {
  private:
    unsigned int m_id;
    mutable std::unordered_map<std::string, int> m_uniformLocationCache;

  public:
    ~GLprogram();

    unsigned int createProgram(unsigned int vs, unsigned int fs);
    void bind() const;
    void unbind() const;

    void setUniform4f(const std::string &name, float v0, float v1, float v2,
                      float v3) const;
    void setUniformMat4f(const std::string &name, const glm::mat4 &matrix) const;

    void setUniform3f(const std::string &name, float v0, float v1, float v2) const;

    void setUniform1f(const std::string &name, float v) const;
    void setUniform1i(const std::string &name, int v) const;

  private:
    int getUniformLocation(const std::string name) const;
};
