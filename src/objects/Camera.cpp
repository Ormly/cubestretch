#include "Camera.h"
#include <glm\gtx\transform.hpp>

const float Camera::MOVEMENT_SPEED = 1.0f;

Camera::Camera() : m_position(0.0f, 0.0f, 0.f), m_direction(0.0f, 0.0f, -1.0f), m_UP(0.0f, 1.0f, 0.0f)
{

}

glm::mat4 Camera::getWorldToViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_direction, m_UP);
}

void Camera::updateDirection(const glm::vec2 &mousePositionDelta)
{
    //glm::vec2 positionDelta = updatedMousePosition - m_previousMousePosition;
    //m_previousMousePosition = updatedMousePosition;
    //TODO: fix magix numbers
    if(glm::length(mousePositionDelta) > 100.0f)
        return;
    else
    {
        const float ROTATIONAL_SPEED = 0.1f;
        crossedViewDirection =  glm::cross(m_direction, m_UP);
        glm::mat4 rotator = glm::rotate(glm::radians(-mousePositionDelta.x * ROTATIONAL_SPEED), m_UP) *
                            glm::rotate(glm::radians(-mousePositionDelta.y * ROTATIONAL_SPEED), crossedViewDirection);

        m_direction = glm::mat3(rotator) * m_direction;
    }
}

void Camera::moveBackward()
{
    m_position += -MOVEMENT_SPEED * m_direction;
}

void Camera::moveForward()
{
    m_position += MOVEMENT_SPEED * m_direction;
}

void Camera::strafeLeft()
{
    m_position += -MOVEMENT_SPEED * crossedViewDirection;
}

void Camera::strafeRight()
{
    m_position += MOVEMENT_SPEED * crossedViewDirection;
}

void Camera::moveUp()
{
    m_position += MOVEMENT_SPEED * m_UP;
}

void Camera::moveDown()
{
    m_position += -MOVEMENT_SPEED * m_UP;
}
