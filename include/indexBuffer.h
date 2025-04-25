#pragma once

class indexBuffer {
private:
    unsigned int m_id;
    unsigned int m_count;

public:
    indexBuffer(const void* data, unsigned int count);
    ~indexBuffer();

    void bind() const;
    void unbind() const;
};
