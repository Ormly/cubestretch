#include "Cube.h"

Cube::Cube(glm::vec3 center, GLfloat halfSideLength, std::array<GLint, 6> &neighbors, glm::vec4 color, GLuint id):
m_center(center), m_halfSideLength(halfSideLength), m_neighbors(neighbors), m_color(color), m_id(id)
{
    updateVertices();

    m_vertexArray = new VertexArray();
    m_vertexBuffer = new VertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(3);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer = new IndexBuffer(m_indices.data(), m_indices.size());
    m_vertexBuffer->unbind();
    m_vertexArray->unbind();
    m_indexBuffer->unbind();
}

void Cube::updateVertices()
{
    m_vertices.clear();
    m_vertices =
    {
        m_center.x - m_halfSideLength, m_center.y - m_halfSideLength, m_center.z + m_halfSideLength, //0 (0,1,2), front bottom left
        m_center.x + m_halfSideLength, m_center.y - m_halfSideLength, m_center.z + m_halfSideLength, //1 (3,4,5), front bottom right
        m_center.x + m_halfSideLength, m_center.y + m_halfSideLength, m_center.z + m_halfSideLength, //2 (6,7,8), front top right
        m_center.x - m_halfSideLength, m_center.y + m_halfSideLength, m_center.z + m_halfSideLength, //3 (9,10,11), front top left
        m_center.x - m_halfSideLength, m_center.y - m_halfSideLength, m_center.z - m_halfSideLength, //4 (12,13,14), back bottom left
        m_center.x + m_halfSideLength, m_center.y - m_halfSideLength, m_center.z - m_halfSideLength, //5 (15,16,17), back bottom right
        m_center.x + m_halfSideLength, m_center.y + m_halfSideLength, m_center.z - m_halfSideLength, //6 (18,19,20), back top right
        m_center.x - m_halfSideLength, m_center.y + m_halfSideLength, m_center.z - m_halfSideLength, //7 (21,22,23), back top left
    };
}

void Cube::resetBuffer()
{
    m_vertexArray->bind();
    m_vertexBuffer = new VertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));
    VertexBufferLayout frameVertexBufferLayout;
    frameVertexBufferLayout.push<GLfloat>(3);
    m_vertexArray->addBuffer(*m_vertexBuffer, frameVertexBufferLayout);
    m_indexBuffer->bind();
}

VertexArray *Cube::getVertexArray() const
{
    return m_vertexArray;
}

IndexBuffer *Cube::getIndexBuffer() const
{
    return m_indexBuffer;
}

glm::vec3 Cube::getCenter() const
{
    return m_center;
}

std::array<GLint, 6> Cube::getNeighbors() const
{
    return m_neighbors;
}

GLint Cube::getUpNeighbor() const
{
    return m_neighbors.at(0);
}

GLint Cube::getDownNeighbor() const
{
    return m_neighbors.at(1);
}

GLint Cube::getLeftNeighbor() const
{
    return m_neighbors.at(2);
}

GLint Cube::getRightNeighbor() const
{
    return m_neighbors.at(3);
}

GLint Cube::getFrontNeighbor() const
{
    return m_neighbors.at(4);
}

GLint Cube::getBackNeighbor() const
{
    return m_neighbors.at(5);
}

glm::vec4 Cube::getColor() const
{
    return m_color;
}

void Cube::addNeighbor(GLuint neighbor, Direction direction)
{
    switch(direction)
    {
        case UP:
            m_neighbors[0] = neighbor;
            break;
        case DOWN:
            m_neighbors[1] = neighbor;
            break;
        case LEFT:
            m_neighbors[2] = neighbor;
            break;
        case RIGHT:
            m_neighbors[3] = neighbor;
            break;
        case FRONT:
            m_neighbors[4] = neighbor;
            break;
        case BACK:
            m_neighbors[5] = neighbor;
            break;
    }
}

GLuint Cube::getID() const
{
    return m_id;
}

void Cube::setColor(glm::vec4 color)
{
    m_color = color;
}

