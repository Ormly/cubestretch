#include "Cube.h"

Cube::Cube(glm::vec3 center, GLfloat halfSideLength, std::array<Cube*, 6> &neighbors, glm::vec4 color):
m_center(center), m_halfSideLength(halfSideLength), m_neighbors(neighbors), m_color(color)
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
        m_center.x - m_halfSideLength, m_center.y - m_halfSideLength, m_center.z + m_halfSideLength, //front bottom left
        m_center.x + m_halfSideLength, m_center.y - m_halfSideLength, m_center.z + m_halfSideLength, //front bottom right
        m_center.x + m_halfSideLength, m_center.y + m_halfSideLength, m_center.z + m_halfSideLength, //front top right
        m_center.x - m_halfSideLength, m_center.y + m_halfSideLength, m_center.z + m_halfSideLength, //front top left
        m_center.x - m_halfSideLength, m_center.y - m_halfSideLength, m_center.z - m_halfSideLength, //back bottom left
        m_center.x + m_halfSideLength, m_center.y - m_halfSideLength, m_center.z - m_halfSideLength, //back bottom right
        m_center.x + m_halfSideLength, m_center.y + m_halfSideLength, m_center.z - m_halfSideLength, //back top right
        m_center.x - m_halfSideLength, m_center.y + m_halfSideLength, m_center.z - m_halfSideLength, //back top left
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

std::array<Cube *, 6> Cube::getNeighbors() const
{
    return m_neighbors;
}

Cube *Cube::getUpNeighbor() const
{
    return m_neighbors.at(0);
}

Cube *Cube::getDownNeighbor() const
{
    return m_neighbors.at(1);
}

Cube *Cube::getLeftNeighbor() const
{
    return m_neighbors.at(2);
}

Cube *Cube::getRightNeighbor() const
{
    return m_neighbors.at(3);
}

Cube *Cube::getFrontNeighbor() const
{
    return m_neighbors.at(4);
}

Cube *Cube::getBackNeighbor() const
{
    return m_neighbors.at(5);
}

glm::vec4 Cube::getColor() const
{
    return m_color;
}

