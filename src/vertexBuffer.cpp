#include "vertexBuffer.h"
#include "glad/glad.h"

vertexBuffer::vertexBuffer(const void *data, unsigned int size) {
  glGenBuffers(1, &m_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_id);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

vertexBuffer::~vertexBuffer() { glDeleteBuffers(1, &m_id); }

void vertexBuffer::bind() const { glBindBuffer(GL_ARRAY_BUFFER, m_id); }

void vertexBuffer::unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
