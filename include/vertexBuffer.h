#pragma once

class vertexBuffer {
private:
    unsigned int m_id;
public:
    vertexBuffer(const void* data, unsigned int size);
    ~vertexBuffer();


    void Bind() const;
    void Unbind() const;
    };