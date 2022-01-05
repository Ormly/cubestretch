#ifndef CUBESTRETCH_CAMERA_H
#define CUBESTRETCH_CAMERA_H

#include <glm\glm.hpp>

class Camera
{
private:
    glm::vec3 m_position;
    glm::vec3 m_direction;
    const glm::vec3 m_UP;
    glm::vec2 m_previousMousePosition;
    static const float MOVEMENT_SPEED;
    glm::vec3 m_crossedViewDirection;
public:
    Camera();
    glm::mat4 getWorldToViewMatrix() const;
    void updateDirection(const glm::vec2& mousePositionDelta);
    void moveBackward();
    void moveForward();
    void strafeLeft();
    void strafeRight();
    void moveUp();
    void moveDown();
    glm::vec3 getDirection() const;
};


#endif //CUBESTRETCH_CAMERA_H
