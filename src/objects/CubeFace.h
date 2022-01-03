#ifndef CUBESTRETCH_CUBEFACE_H
#define CUBESTRETCH_CUBEFACE_H

#include "Rectangle.h"

class CubeFace: public Rectangle
{
protected:
    std::vector<GLfloat> m_color;

public:
    CubeFace(glm::vec3 center, GLfloat width, GLfloat height, std::vector<GLfloat> color);
    std::vector<GLfloat> getColor() const;
};


#endif //CUBESTRETCH_CUBEFACE_H
