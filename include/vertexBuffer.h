#pragma once

class vertexBuffer {
  private:
    unsigned int m_id;

  public:
    vertexBuffer(const void *data, unsigned int size);
    ~vertexBuffer();

    void bind() const;
    void unbind() const;
};
