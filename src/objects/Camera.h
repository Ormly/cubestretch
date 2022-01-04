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
public:
    Camera();
    glm::mat4 getWorldToViewMatrix() const;
    void mouseUpdate(const glm::vec2& updatedMousePosition);

};


#endif //CUBESTRETCH_CAMERA_H
