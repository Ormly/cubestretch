#ifndef CUBESTRETCH_CUBESTRETCHAPP_H
#define CUBESTRETCH_CUBESTRETCHAPP_H

#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include "renderer/VertexArray.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shaders.h"
#include "renderer/Renderer.h"

GLFWwindow* window;
GLfloat windowWidth;
GLfloat windowHeight;

GLdouble deltaTime;
GLdouble previousTime;
GLdouble limitFPS;

Renderer renderer;
Shaders* shaders;

glm::mat4 projection;
glm::mat4 identity;

GLboolean initializeWindow();
void initializeContents();
void update();
void render();

#endif //CUBESTRETCH_CUBESTRETCHAPP_H
