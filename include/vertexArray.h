#pragma once

#include "vertexArray.h"

#include "vertexLayout.h"
#include "vertexBuffer.h"

class vertexArray {
private:
    unsigned int m_id;

public:
    vertexArray();
    ~vertexArray();

    void addBuffer(vertexBuffer &vb, const vertexLayout& layout);
    void bind() const;
    void unbind() const;
};
