#ifndef CUBESTRETCH_MOUSEINPUT_H
#define CUBESTRETCH_MOUSEINPUT_H

#include <glm\glm.hpp>

enum MouseState
{
    PRESSED,
    RELEASED
};

class MouseInput
{
private:
    glm::vec2 m_previousPosition;
    glm::vec2 m_currentPosition;
    glm::vec2 m_positionDelta;
    MouseState m_state;

public:
    MouseInput();
    void setCurrentPosition(const glm::vec2& updatedPosition);
    void setState(MouseState state);
    glm::vec2 getPreviousPosition() const;
    glm::vec2 getCurrentPosition() const;
    glm::vec2 getPositionDelta() const;
    MouseState getState() const;
};


#endif //CUBESTRETCH_MOUSEINPUT_H
