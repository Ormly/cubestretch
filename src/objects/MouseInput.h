#ifndef CUBESTRETCH_MOUSEINPUT_H
#define CUBESTRETCH_MOUSEINPUT_H

#include <glm\glm.hpp>

class MouseInput
{
private:
    glm::vec2 m_previousPosition;
    glm::vec2 m_updatedPosition;
    glm::vec2 m_positionDelta;

public:
    MouseInput();
    void setUpdatedPosition(const glm::vec2& updatedPosition);
    glm::vec2 getPreviousPosition() const;
    glm::vec2 getUpdatedPosition() const;
    glm::vec2 getPositionDelta() const;
};


#endif //CUBESTRETCH_MOUSEINPUT_H
