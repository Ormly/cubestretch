#ifndef CUBESTRETCH_INDEXBUFFER_H
#define CUBESTRETCH_INDEXBUFFER_H

#include "GL/glew.h"

class IndexBuffer
{
private:
    GLuint m_bufferID;
    GLuint m_numberOfIndices;
public:
    IndexBuffer(const GLuint* data, GLuint numberOfIndices);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;

    GLuint getNumberOfIndices() const;
};

#endif //CUBESTRETCH_INDEXBUFFER_H

