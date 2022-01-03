#ifndef CUBESTRETCH_RENDERER_H
#define CUBESTRETCH_RENDERER_H

#include "GL/glew.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shaders.h"

void glClearError();
GLboolean glLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    void clear() const;
    void draw(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const Shaders& shaders) const;
};


#endif //CUBESTRETCH_RENDERER_H
