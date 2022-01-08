#include "Cube.h"

Cube::Cube(glm::vec3 center, GLfloat halfSideLength, std::array<GLint, 6> &neighbors, glm::vec3 color, GLuint id, GLfloat edgeStripWidth, glm::vec3 edgeStripColor):
        m_center(center), m_neighbors(neighbors), m_cubeColor(color), m_id(id), m_halfSideLength(halfSideLength), m_edgeStripWidth(edgeStripWidth), m_edgeStripColor(edgeStripColor)
{
    updateVertices();

    m_vertexArray = new VertexArray();
    m_vertexBuffer = new VertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));

    VertexBufferLayout cubeVertexBufferLayout;
    cubeVertexBufferLayout.push<GLfloat>(3);
    m_vertexArray->addBuffer(*m_vertexBuffer, cubeVertexBufferLayout);
    cubeVertexBufferLayout.push<GLfloat>(3);
    m_vertexArray->addBuffer(*m_vertexBuffer, cubeVertexBufferLayout);

    m_indexBuffer = new IndexBuffer(m_indices.data(), m_indices.size());
    m_vertexBuffer->unbind();
    m_vertexArray->unbind();
    m_indexBuffer->unbind();
}

//I think this is the worst thing I've ever done. Turn back while you still can
//1/4th of the way in I realized how stupid this was, but by then I was committed. Should have used a texture or something instead.
void Cube::updateVertices()
{
    m_vertices.clear();
    GLfloat gap = 0.01f;

    GLfloat centerX = m_center.x;
    GLfloat centerY = m_center.y;
    GLfloat centerZ = m_center.z;
    
    GLfloat cubeColorX = m_cubeColor.x;
    GLfloat cubeColorY = m_cubeColor.y;
    GLfloat cubeColorZ = m_cubeColor.z;
    
    GLfloat edgeColorX = m_edgeStripColor.x;
    GLfloat edgeColorY = m_edgeStripColor.y;
    GLfloat edgeColorZ = m_edgeStripColor.z;

    m_vertices =
    {
        //###cube###
        centerX - m_halfSideLength + gap, centerY - m_halfSideLength + gap, centerZ + m_halfSideLength - gap, //0 (0,1,2), front bottom left
        cubeColorX             , cubeColorY              , cubeColorZ              ,
        centerX + m_halfSideLength - gap, centerY - m_halfSideLength + gap, centerZ + m_halfSideLength - gap, //1 (6,7,8), front bottom right
        cubeColorX             , cubeColorY              , cubeColorZ              ,
        centerX + m_halfSideLength - gap, centerY + m_halfSideLength - gap, centerZ + m_halfSideLength - gap, //2 (12,13,14), front top right
        cubeColorX             , cubeColorY              , cubeColorZ              ,
        centerX - m_halfSideLength + gap, centerY + m_halfSideLength - gap, centerZ + m_halfSideLength - gap, //3 (18,19,20), front top left
        cubeColorX             , cubeColorY              , cubeColorZ              ,
        centerX - m_halfSideLength + gap, centerY - m_halfSideLength + gap, centerZ - m_halfSideLength + gap, //4 (24,25,26), back bottom left
        cubeColorX             , cubeColorY              , cubeColorZ              ,
        centerX + m_halfSideLength - gap, centerY - m_halfSideLength + gap, centerZ - m_halfSideLength + gap, //5 (30,31,32), back bottom right
        cubeColorX             , cubeColorY              , cubeColorZ              ,
        centerX + m_halfSideLength - gap, centerY + m_halfSideLength - gap, centerZ - m_halfSideLength + gap, //6 (36,37,38), back top right
        cubeColorX             , cubeColorY              , cubeColorZ              ,
        centerX - m_halfSideLength + gap, centerY + m_halfSideLength - gap, centerZ - m_halfSideLength + gap, //7 (42,43,44), back top left
        cubeColorX             , cubeColorY              , cubeColorZ,

        //###edges###
        //#front#
        //-left subsquare- (8,9,10,10,11,8)
        //bottom left vertex: 8
        centerX - m_halfSideLength, centerY - m_halfSideLength, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //bottom right vertex: 9
        centerX - m_halfSideLength + m_edgeStripWidth, centerY - m_halfSideLength, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top right vertex: 10
        centerX - m_halfSideLength + m_edgeStripWidth, centerY + m_halfSideLength, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top left vertex: 11
        centerX - m_halfSideLength, centerY + m_halfSideLength, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //-down subsquare- (8,12,13,13,14,8)
        //bottom right vertex: 12
        centerX + m_halfSideLength, centerY - m_halfSideLength, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top right vertex: 13
        centerX + m_halfSideLength, centerY - m_halfSideLength + m_edgeStripWidth, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top left vertex: 14
        centerX - m_halfSideLength, centerY - m_halfSideLength + m_edgeStripWidth, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //-right subsquare- (15,12,16,16,17,15)
        //bottom left vertex: 15
        centerX + m_halfSideLength - m_edgeStripWidth, centerY - m_halfSideLength, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top right vertex: 16
        centerX + m_halfSideLength, centerY + m_halfSideLength, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top left vertex: 17
        centerX + m_halfSideLength - m_edgeStripWidth, centerY + m_halfSideLength, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //-top subsquare- (18,19,16,16,11,18)
        //bottom left vertex: 18
        centerX - m_halfSideLength, centerY + m_halfSideLength - m_edgeStripWidth, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //bottom right vertex: 19
        centerX + m_halfSideLength, centerY + m_halfSideLength - m_edgeStripWidth, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //#left#
        //-right subsquare- (21,20,23,23,22,21)
        //bottom right vertex: 20
        centerX - m_halfSideLength, centerY - m_halfSideLength, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //bottom left vertex: 21
        centerX - m_halfSideLength, centerY - m_halfSideLength, centerZ - m_halfSideLength + m_edgeStripWidth,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top left vertex: 22
        centerX - m_halfSideLength, centerY + m_halfSideLength, centerZ - m_halfSideLength + m_edgeStripWidth,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top right vertex: 23
        centerX - m_halfSideLength, centerY + m_halfSideLength, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //-down subsquare- (20,8,24,24,25,20)
        //top left vertex: 24
        centerX - m_halfSideLength, centerY - m_halfSideLength + m_edgeStripWidth, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top right vertex: 25
        centerX - m_halfSideLength, centerY - m_halfSideLength + m_edgeStripWidth, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //-left subsquare- (8,26,27,27,11,8)
        //bottom right vertex: 26
        centerX - m_halfSideLength, centerY - m_halfSideLength, centerZ + m_halfSideLength - m_edgeStripWidth,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top right vertex: 27
        centerX - m_halfSideLength, centerY + m_halfSideLength, centerZ + m_halfSideLength - m_edgeStripWidth,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //-top subsquare- (28,29,11,11,23,28)
        //bottom left vertex: 28
        centerX - m_halfSideLength, centerY + m_halfSideLength - m_edgeStripWidth, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //bottom right vertex: 29
        centerX - m_halfSideLength, centerY + m_halfSideLength - m_edgeStripWidth, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,


        //#right#
        //-down subsquare- (30,12,31,31,32,30)
        //bottom left vertex: 30
        centerX + m_halfSideLength, centerY - m_halfSideLength, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top right vertex: 31
        centerX + m_halfSideLength, centerY - m_halfSideLength + m_edgeStripWidth, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top left vertex: 32
        centerX + m_halfSideLength, centerY - m_halfSideLength + m_edgeStripWidth, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //-left subsquare- (30,33,34,34,35,30)
        //bottom right vertex: 33
        centerX + m_halfSideLength, centerY - m_halfSideLength, centerZ - m_halfSideLength + m_edgeStripWidth,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top right vertex: 34
        centerX + m_halfSideLength, centerY + m_halfSideLength, centerZ - m_halfSideLength + m_edgeStripWidth,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top left vertex: 35
        centerX + m_halfSideLength, centerY + m_halfSideLength, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //-right subsquare- (36,12,16,16,37,36)
        //bottom left vertex: 36
        centerX + m_halfSideLength, centerY - m_halfSideLength, centerZ + m_halfSideLength - m_edgeStripWidth,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //top left vertex: 37
        centerX + m_halfSideLength, centerY + m_halfSideLength, centerZ + m_halfSideLength - m_edgeStripWidth,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //-top subsquare- (38,39,16,16,35,38)
        //bottom left vertex: 38
        centerX + m_halfSideLength, centerY + m_halfSideLength - m_edgeStripWidth, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,
        //bottom right vertex: 39
        centerX + m_halfSideLength, centerY + m_halfSideLength - m_edgeStripWidth, centerZ + m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //#down#
        //-down subsquare- (8,12,36,36,26,8)
        //-top subsquare- (21,33,30,30,20,21)

        //-left subsquare- (8,9,40,40,20,8)
        //top right vertex: 40
        centerX - m_halfSideLength + m_edgeStripWidth, centerY - m_halfSideLength, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //-right subsquare- (15,12,30,30,41,15)
        //top left vertex: 41
        centerX + m_halfSideLength - m_edgeStripWidth, centerY - m_halfSideLength, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //#up#
        //-bottom subsquare- (11,16,37,37,27,11)
        //-top subsquare- (22,34,35,35,23,22)

        //-left subsquare- (11,10,42,42,23,11)
        //top right vertex: 42
        centerX - m_halfSideLength + m_edgeStripWidth, centerY + m_halfSideLength, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //-right subsquare (17,16,35,35,43,17)
        //top left vertex: 43
        centerX + m_halfSideLength - m_edgeStripWidth, centerY + m_halfSideLength, centerZ - m_halfSideLength,
        edgeColorX         , edgeColorY         , edgeColorZ,

        //#back#
        //-bottom subsquare- (20,30,32,32,25,20)
        //-top subsquare- (28,38,35,35,23,28)
        //-left subsquare- (20,40,42,42,23,20)
        //-right subsquare (41,30,35,35,43,41)
    };
}

void Cube::resetBuffer()
{
    m_vertexArray->bind();
    m_vertexBuffer = new VertexBuffer(m_vertices.data(), m_vertices.size() * sizeof(GLfloat));

    VertexBufferLayout cubeVertexBufferLayout;
    cubeVertexBufferLayout.push<GLfloat>(3);
    m_vertexArray->addBuffer(*m_vertexBuffer, cubeVertexBufferLayout);
    cubeVertexBufferLayout.push<GLfloat>(3);
    m_vertexArray->addBuffer(*m_vertexBuffer, cubeVertexBufferLayout);

    m_vertexArray->addBuffer(*m_vertexBuffer, cubeVertexBufferLayout);
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

glm::vec3 Cube::getCubeColor() const
{
    return m_cubeColor;
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

void Cube::setCubeColor(glm::vec3 color)
{
    m_cubeColor = color;
    updateVertices();
    resetBuffer();
}

glm::vec3 Cube::getEdgeStripColor() const
{
    return m_edgeStripColor;
}

void Cube::setEdgeStripColor(glm::vec3 color)
{
    m_edgeStripColor = color;
    updateVertices();
    resetBuffer();
}

