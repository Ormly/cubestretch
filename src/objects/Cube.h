#ifndef CUBESTRETCH_CUBE_H
#define CUBESTRETCH_CUBE_H

#include <glm/glm.hpp>
#include "../renderer/VertexArray.h"
#include "../renderer/IndexBuffer.h"
#include <array>
#include <memory>

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FRONT,
    BACK
};

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
        4,5,6,6,7,4, //back

        //front edges
        8,9,10,10,11,8,
        8,12,13,13,14,8,
        15,12,16,16,17,15,
        18,19,16,16,11,18,

        //left edges
        21,20,23,23,22,21,
        20,8,24,24,25,20,
        8,26,27,27,11,8,
        28,29,11,11,23,28,

        //right edges
        30,12,31,31,32,30,
        30,33,34,34,35,30,
        36,12,16,16,37,36,
        38,39,16,16,35,38,

        //down edges
        8,12,36,36,26,8,
        21,33,30,30,20,21,
        8,9,40,40,20,8,
        15,12,30,30,41,15,

        //up edges
        11,16,37,37,27,11,
        22,34,35,35,23,22,
        11,10,42,42,23,11,
        17,16,35,35,43,17,

        //back edges
        20,30,32,32,25,20,
        28,38,35,35,23,28,
        20,40,42,42,23,20,
        41,30,35,35,43,41
    };
    glm::vec3 m_center;
    std::vector<GLfloat> m_vertices;
    VertexArray* m_vertexArray;
    VertexBuffer* m_vertexBuffer;
    IndexBuffer* m_indexBuffer;
    //std::array<CubeFace*, 6> m_cubeFaces; //up,down,left,right,front,back
    std::array<GLint, 6> m_neighbors; //up,down,left,right,front,back
    glm::vec3 m_cubeColor;
    glm::vec3 m_edgeStripColor;
    GLuint m_id;
    GLfloat m_halfSideLength;
    GLfloat m_edgeStripWidth;
    void updateVertices();
    void resetBuffer();
public:
    Cube(glm::vec3 center, GLfloat halfSideLength, std::array<GLint, 6> &neighbors, glm::vec3 cubeColor, GLuint id, GLfloat edgeStripWidth, glm::vec3 edgeStripColor);
    glm::vec3 getCenter() const;
    void addNeighbor(GLuint neighborID, Direction direction);
    std::array<GLint, 6> getNeighbors() const;
    GLint getUpNeighbor() const;
    GLint getDownNeighbor() const;
    GLint getLeftNeighbor() const;
    GLint getRightNeighbor() const;
    GLint getFrontNeighbor() const;
    GLint getBackNeighbor() const;
    VertexArray* getVertexArray() const;
    IndexBuffer* getIndexBuffer() const;
    glm::vec3 getCubeColor() const;
    GLuint getID() const;
    void setCubeColor(glm::vec3 color);
    glm::vec3 getEdgeStripColor() const;
    void setEdgeStripColor(glm::vec3 color);
};

#endif //CUBESTRETCH_CUBE_H
