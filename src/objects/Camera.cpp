#include "Camera.h"
#include <glm\gtx\transform.hpp>

Camera::Camera() : m_position(0.0f, 0.0f, 0.f), m_direction(0.0f, 0.0f, -1.0f), m_UP(0.0f, 1.0f, 0.0f)
{

}

glm::mat4 Camera::getWorldToViewMatrix() const
{
    return glm::lookAt(m_position, m_position + m_direction, m_UP);
}

void Camera::mouseUpdate(const glm::vec2 &updatedMousePosition)
{
    glm::vec2 positionDelta = updatedMousePosition - m_previousMousePosition;
    m_previousMousePosition = updatedMousePosition;
    //TODO: fix magix numbers
    if(glm::length(positionDelta) > 100.0f)
        return;
    else
    {
        const float ROTATIONAL_SPEED = 0.05f;
        glm::vec3 crossedViewDirection =  glm::cross(m_direction, m_UP);
        glm::mat4 rotator = glm::rotate(glm::radians(-positionDelta.x * ROTATIONAL_SPEED), m_UP) *
                            glm::rotate(glm::radians(-positionDelta.y * ROTATIONAL_SPEED), crossedViewDirection);

        m_direction = glm::mat3(rotator) * m_direction;
    }
}
