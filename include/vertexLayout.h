#pragma once

#include "glad/glad.h"
#include <assert.h>
#include <iostream>
#include <vector>

struct vertexAttribute {
  unsigned int type;
  unsigned int count;
  bool normalized;

  static unsigned int getSizeOfType(unsigned int type) {
    switch (type) {
    case GL_FLOAT:
      return 4;
      break;
    case GL_UNSIGNED_INT:
      return 4;
      break;
    case GL_UNSIGNED_BYTE:
      return 1;
      break;
    }
  }
};

class vertexLayout {
private:
  std::vector<vertexAttribute> m_attributes;
  unsigned int m_stride;

public:
  vertexLayout() : m_stride(0) {}

  template <typename T> inline void push(const unsigned int count) {
    std::cerr << "No matching OpenGL type in vertexLayout.push()\n";
    assert(false);
  }

  inline const std::vector<vertexAttribute> &getAttributes() const {
    return m_attributes;
  }

  inline unsigned int getStride() const { return m_stride; }
};

template <> inline void vertexLayout::push<float>(const unsigned int count) {
  m_attributes.push_back({GL_FLOAT, count, false});
  m_stride += 4 * count;
}

template <>
inline void vertexLayout::push<unsigned int>(const unsigned int count) {
  m_attributes.push_back({GL_UNSIGNED_INT, count, false});
  m_stride += 4 * count;
}

template <>
inline void vertexLayout::push<unsigned char>(const unsigned int count) {
  m_attributes.push_back({GL_UNSIGNED_BYTE, count, true});
  m_stride += 1 * count;
}
