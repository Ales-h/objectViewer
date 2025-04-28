#include "shader.h"
#include <iostream>
#include <fstream>

shader::shader(GLenum type, std::string path): m_filePath(path), m_type(type) {
    compileShader();
}
shader::~shader() {
    glDeleteShader(m_id);
}

void shader::compileShader() {
    std::string s = loadShader();
    const char *src = s.c_str();

    m_id = glCreateShader(m_type);
    glShaderSource(m_id, 1, &src, nullptr);
    glCompileShader(m_id);
    GLint ok = 0;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char buf[512];
        glGetShaderInfoLog(m_id, 512, nullptr, buf);
        std::cerr << "Shader compile error: " << buf << "\n";
        std::exit(-1);
    }
}

std::string shader::loadShader() const {

    std::ifstream shader_file(m_filePath);
    if(!shader_file.is_open()){
        std::cerr << "Failed to open a shader file!!\n";
    }

    std::string src = "";
    std::string line;
    while(std::getline(shader_file, line)){
        src += line;
        src.push_back('\n');
    }

    return src;
}
