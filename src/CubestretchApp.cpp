#include "CubestretchApp.h"
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(glfwWindow, GLFW_TRUE);
}

int main()
{
    windowWidth = 1280.0f;
    windowHeight = 960.0f;

    if(!initializeWindow())
        exit(EXIT_FAILURE);

    shaders = new Shaders("../res/shaders/VertexShader.vs",
                          "../res/shaders/FragmentShader.fs");
    shaders->bind();

    initializeContents();

    while (!glfwWindowShouldClose(window))
    {
        GLdouble currentTime = glfwGetTime();
        deltaTime += (currentTime - previousTime) / limitFPS;
        previousTime = currentTime;

        while (deltaTime >= 1.0)
        {
            glfwPollEvents();
            update();
            deltaTime--;
        }

        render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

void update()
{

}

void render()
{

}

void initializeContents()
{
    projection = glm::ortho(0.0f, windowWidth, 0.0f, windowHeight);
    identity = glm::mat4(1.0f);

    limitFPS = 1.0 / 60.0;
    previousTime = glfwGetTime();
    deltaTime = 0;
}

GLboolean initializeWindow()
{
    if (!glfwInit())
    {
        std::cout <<
                  "GLFW Error: Library could not be initialized!" <<
                  std::endl;

        return GL_FALSE;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

    window = glfwCreateWindow(windowWidth, windowHeight, "cubestretch", nullptr, nullptr);
    if (!window)
    {
        std::cout <<
                  "GLFW Error: Window context could not be initialized!" <<
                  std::endl;

        return GL_FALSE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cout <<
                  "GLEW Error: Could not be initialized!" <<
                  std::endl;
        return GL_FALSE;
    }

    //glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetKeyCallback(window, key_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return GL_TRUE;
}
