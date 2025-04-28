#pragma once
#include "glad/glad.h"
#include <string>

class shader {
  private:
    unsigned int m_id;
    std::string m_filePath;
    GLenum m_type;

  public:
    shader(GLenum type, std::string path);
    ~shader();

    void compileShader();
    unsigned int getId() const { return m_id; }

  private:
    std::string loadShader() const;
};
