#include "CubeFace.h"

CubeFace::CubeFace(glm::vec3 center, GLfloat width, GLfloat height, std::vector<GLfloat> color):
Rectangle(center, width, height), m_color(std::move(color))
{
}

std::vector<GLfloat> CubeFace::getColor() const
{
    return m_color;
}
