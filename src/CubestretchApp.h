#ifndef CUBESTRETCH_CUBESTRETCHAPP_H
#define CUBESTRETCH_CUBESTRETCHAPP_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shaders.h"
#include "renderer/Renderer.h"
#include "objects/Cube.h"
#include "objects/Camera.h"
#include "objects/MouseInput.h"

enum State
{
    NONE,
    BUILDING,
    SELECTING
};

GLFWwindow* m_window;
GLfloat m_windowWidth;
GLfloat m_windowHeight;

GLdouble m_deltaTime;
GLdouble m_previousTime;
GLdouble m_limitFPS;

Renderer m_renderer;
Shaders* m_shaders;

Camera* m_camera;
MouseInput* m_mouse;

glm::mat4 m_identity;
glm::mat4 m_translation;
glm::mat4 m_rotation;
glm::mat4 m_projection;
glm::mat4 m_modelTransform;

State m_state;
std::vector<Cube*> m_cubes;
GLuint m_selectedCubeID;

GLboolean initializeWindow();
void initializeContents();
void initializeOriginCube();
void checkInput();
void render();
GLuint createCube(const Cube* sourceCube, Direction direction);
std::array<GLint, 6> calculateAndSetNeighbors(glm::vec3 cubeCenter);
Cube* getCubeFromID(GLuint cubeID);

#endif //CUBESTRETCH_CUBESTRETCHAPP_H
