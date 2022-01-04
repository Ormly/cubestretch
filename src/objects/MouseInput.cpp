#include "MouseInput.h"

MouseInput::MouseInput(): m_previousPosition(0.0f, 0.0f), m_currentPosition(0.0f, 0.0f), m_state(RELEASED)
{

}

glm::vec2 MouseInput::getPreviousPosition() const
{
    return m_previousPosition;
}

glm::vec2 MouseInput::getCurrentPosition() const
{
    return m_currentPosition;
}

glm::vec2 MouseInput::getPositionDelta() const
{
    return m_positionDelta;
}

void MouseInput::setCurrentPosition(const glm::vec2 &updatedPosition)
{
    m_currentPosition = updatedPosition;
    m_positionDelta = m_currentPosition - m_previousPosition;
    m_previousPosition = m_currentPosition;
}

void MouseInput::setState(MouseState state)
{
    m_state = state;
}

MouseState MouseInput::getState() const
{
    return m_state;
}
