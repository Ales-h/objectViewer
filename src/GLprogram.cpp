#include "GLprogram.h"
#include "glad/glad.h"

#include <iostream>

GLprogram::~GLprogram() {
    if (m_id != -1) {
        glDeleteProgram(m_id);
    }
}

unsigned int GLprogram::createProgram(unsigned int vs, unsigned int fs) {
    m_id = glCreateProgram();

    glAttachShader(m_id, vs);
    glAttachShader(m_id, fs);
    glLinkProgram(m_id);
    glValidateProgram(m_id);

    return m_id;
}

void GLprogram::bind() const { glUseProgram(m_id); }
void GLprogram::unbind() const { glUseProgram(0); }

void GLprogram::setUniform4f(const std::string &name, float v0, float v1, float v2,
                             float v3) const {
    glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}
void GLprogram::setUniformMat4f(const std::string &name, const glm::mat4 &matrix) const {
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

void GLprogram::setUniform3f(const std::string &name, float v0, float v1,
                             float v2) const {
    glUniform3f(getUniformLocation(name), v0, v1, v2);
}

void GLprogram::setUniform1f(const std::string &name, float v) const {
    glUniform1f(getUniformLocation(name), v);
}
void GLprogram::setUniform1i(const std::string &name, int v) const {
    glUniform1i(getUniformLocation(name), v);
}

int GLprogram::getUniformLocation(const std::string name) const {
    if (m_uniformLocationCache.find(name) != m_uniformLocationCache.end()) {
        return m_uniformLocationCache[name];
    }
    int location = glGetUniformLocation(m_id, name.c_str());
    if (location == -1) {
        std::cout << "Error: Uniform " << name << " doesnt exist!";
    }
    m_uniformLocationCache[name] = location;

    return location;
}
