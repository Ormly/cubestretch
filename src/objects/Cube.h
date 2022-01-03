#ifndef CUBESTRETCH_CUBE_H
#define CUBESTRETCH_CUBE_H

#include "CubeFace.h"
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"
#include <array>
#include <memory>

class Cube
{
private:
    std::vector<GLuint> m_indices =
    {
        3,2,6,6,7,3, //up
        0,1,5,5,4,0, //down
        0,4,7,7,3,0, //left
        1,5,6,6,2,1, //right
        0,1,2,2,3,0, //front
        4,5,6,6,7,4 //back
    };
    glm::vec3 m_center;
    GLfloat m_halfSideLength;
    std::vector<GLfloat> m_vertices;
    VertexArray* m_vertexArray;
    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;
    //std::array<CubeFace*, 6> m_cubeFaces; //up,down,left,right,front,back
    std::array<Cube*, 6> m_neighbors; //up,down,left,right,front,back
    glm::vec4 m_color;

    void updateVertices();
    void resetBuffer();
public:
    Cube(glm::vec3 center, GLfloat halfSideLength, std::array<Cube*, 6> &neighbors, glm::vec4 color);
    glm::vec3 getCenter() const;
    std::array<Cube*, 6> getNeighbors() const;
    Cube* getUpNeighbor() const;
    Cube* getDownNeighbor() const;
    Cube* getLeftNeighbor() const;
    Cube* getRightNeighbor() const;
    Cube* getFrontNeighbor() const;
    Cube* getBackNeighbor() const;
    VertexArray* getVertexArray() const;
    IndexBuffer* getIndexBuffer() const;
    glm::vec4 getColor() const;
};

#endif //CUBESTRETCH_CUBE_H
