#include "indexBuffer.h"
#include "glad/glad.h"

indexBuffer::indexBuffer(const void* data, unsigned int count): m_count(count){
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

indexBuffer::~indexBuffer(){
    glDeleteBuffers(1, &m_id);
}

void indexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void indexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
