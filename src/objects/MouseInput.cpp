#include "MouseInput.h"

MouseInput::MouseInput(): m_previousPosition(0.0f, 0.0f), m_updatedPosition(0.0f, 0.0f)
{

}

glm::vec2 MouseInput::getPreviousPosition() const
{
    return m_previousPosition;
}

glm::vec2 MouseInput::getUpdatedPosition() const
{
    return m_updatedPosition;
}

glm::vec2 MouseInput::getPositionDelta() const
{
    return m_positionDelta;
}

void MouseInput::setUpdatedPosition(const glm::vec2 &updatedPosition)
{
    m_updatedPosition = updatedPosition;
    m_positionDelta = m_updatedPosition - m_previousPosition;
    m_previousPosition = m_updatedPosition;
}
