#ifndef CUBESTRETCH_CUBESTRETCHAPP_H
#define CUBESTRETCH_CUBESTRETCHAPP_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shaders.h"
#include "renderer/Renderer.h"
#include "objects/Cube.h"

GLFWwindow* m_window;
GLfloat m_windowWidth;
GLfloat m_windowHeight;

GLdouble m_deltaTime;
GLdouble m_previousTime;
GLdouble m_limitFPS;

Renderer m_renderer;
Shaders* m_shaders;

glm::mat4 m_identity;
glm::mat4 m_translation;
glm::mat4 m_rotation;
glm::mat4 m_projection;
glm::mat4 m_modelTransform;

std::vector<Cube*> m_cubes;

GLboolean initializeWindow();
void initializeContents();
void initializeOriginCube();
void update();
void render();

#endif //CUBESTRETCH_CUBESTRETCHAPP_H
