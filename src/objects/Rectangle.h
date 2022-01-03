#ifndef CUBESTRETCH_RECTANGLE_H
#define CUBESTRETCH_RECTANGLE_H
#include "GL/glew.h"
#include <vector>
#include "glm/glm.hpp"

class Rectangle
{
protected:
    std::vector<GLuint> m_indices =
    {
        0,1,2,
        2,3,0
    };
    glm::vec3 m_center;
    std::vector<GLfloat> m_vertices;
    GLfloat m_width;
    GLfloat m_height;
    void updateVertices();
public:
    Rectangle(glm::vec3 center, GLfloat width, GLfloat height);
    glm::vec3 getCenter() const;
    std::vector<GLfloat> getVertices() const;
    std::vector<GLuint> getIndices() const;
    GLfloat getWidth() const;
    GLfloat getHeight() const;
    virtual std::vector<GLfloat> getCollisionBox() const;
};


#endif //CUBESTRETCH_RECTANGLE_H
