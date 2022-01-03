#ifndef CUBESTRETCH_VERTEXARRAY_H
#define CUBESTRETCH_VERTEXARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
private:
    GLuint m_arrayID;
public:
    VertexArray();
    ~VertexArray();

    void addBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout);
    void bind() const;
    void unbind() const;
};


#endif //CUBESTRETCH_VERTEXARRAY_H
