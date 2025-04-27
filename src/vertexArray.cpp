#include "vertexArray.h"
#include "vertexLayout.h"

vertexArray::vertexArray() {
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);
}

vertexArray::~vertexArray() { glDeleteVertexArrays(1, &m_id); }

void vertexArray::addBuffer(vertexBuffer &vb, const vertexLayout &layout) {
    bind();
    vb.bind();
    unsigned int offset = 0;
    auto attributes = layout.getAttributes();
    int stride = layout.getStride();
    for (int i = 0; i < attributes.size(); ++i) {
        auto att = attributes[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, att.count, att.type, att.normalized, stride,
                              (const void *)offset);
        offset += att.type * vertexAttribute::getSizeOfType(att.type);
    }
}

void vertexArray::bind() const { glBindVertexArray(m_id); }

void vertexArray::unbind() const { glBindVertexArray(0); }
