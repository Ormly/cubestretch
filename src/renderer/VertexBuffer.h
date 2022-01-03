#ifndef CUBESTRETCH_VERTEXBUFFER_H
#define CUBESTRETCH_VERTEXBUFFER_H

#include "GL/glew.h"

class VertexBuffer
{
private:
    GLuint m_bufferID;
public:
    VertexBuffer(const void* data, const GLuint size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};

#endif //CUBESTRETCH_VERTEXBUFFER_H

