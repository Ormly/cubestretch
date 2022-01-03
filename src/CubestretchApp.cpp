#include "CubestretchApp.h"
#include <iostream>
#include <array>

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
    m_windowWidth = 1280.0f;
    m_windowHeight = 960.0f;

    if(!initializeWindow())
        exit(EXIT_FAILURE);

    m_shaders = new Shaders("../res/shaders/VertexShader.vs",
                            "../res/shaders/FragmentShader.fs");

    if(m_shaders->getProgramID() == 0)
        exit(EXIT_FAILURE);

    m_shaders->bind();

    initializeContents();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(m_window))
    {
        GLdouble currentTime = glfwGetTime();
        m_deltaTime += (currentTime - m_previousTime) / m_limitFPS;
        m_previousTime = currentTime;

        while (m_deltaTime >= 1.0)
        {
            glfwPollEvents();
            update();
            m_deltaTime--;
        }

        render();
        glfwSwapBuffers(m_window);
    }

    glfwTerminate();

    return 0;
}

void update()
{

}

void render()
{
    m_renderer.clear();

    for(Cube* cube : m_cubes)
    {
        glm::vec4 cubeColor = cube->getColor();
        m_shaders->setUniform4f("u_color", cubeColor.x, cubeColor.y, cubeColor.z, cubeColor.w);
        m_renderer.draw(*(cube->getVertexArray()), *(cube->getIndexBuffer()), *m_shaders);
    }
}

void initializeContents()
{
    initializeOriginCube();

    //glViewport(0,0,m_windowWidth,m_windowHeight);

    m_identity = glm::mat4(1.0f);
    //m_screenToNDC = glm::ortho(0.0f, m_windowWidth, 0.0f, m_windowHeight, 0.1f, 20.0f);
    m_translation = glm::translate(m_identity, glm::vec3(0.0f, 0.0f, -40.0f));
    m_rotation = glm::rotate(m_identity, glm::radians(15.0f), glm::vec3(1.0f,0.0f,0.0f));
    m_rotation = glm::rotate(m_rotation, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    m_projection = glm::perspective(glm::radians(60.0f), m_windowWidth / m_windowHeight, 0.1f, 50.0f);

    //m_modelTransform = m_projection * m_rotation * m_translation;
    m_modelTransform = m_projection * m_translation * m_rotation;
    //m_modelTransform = m_translation * m_rotation * m_projection;

    //m_shaders->setUniformMat4f("u_screenToNDC", m_screenToNDC);
    m_shaders->setUniformMat4f("u_modelTransform", m_modelTransform);
    //m_shaders->setUniformMat4f("u_translation", m_translation);
    //m_shaders->setUniformMat4f("u_rotation", m_rotation);
    //m_shaders->setUniformMat4f("u_projection", m_projection);

    m_limitFPS = 1.0 / 60.0;
    m_previousTime = glfwGetTime();
    m_deltaTime = 0;
}

void initializeOriginCube()
{
    std::array<Cube*, 6> neighbors = {{nullptr}};
    glm::vec3 originCubeCenter = {0.0f, 0.0f, 0.0f};
    //glm::vec3 originCubeCenter = {m_windowWidth / 2, m_windowHeight / 2, -1.0f};
    glm::vec4 originCubeColor({1.0f, 1.0f, 1.0f, 1.0f});
    Cube* originCube = new Cube(originCubeCenter, 3.0f, neighbors, originCubeColor);
    m_cubes.push_back(originCube);
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

    m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "cubestretch", nullptr, nullptr);
    if (!m_window)
    {
        std::cout <<
                  "GLFW Error: Window context could not be initialized!" <<
                  std::endl;

        return GL_FALSE;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cout <<
                  "GLEW Error: Could not be initialized!" <<
                  std::endl;
        return GL_FALSE;
    }

    //glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glEnable(GL_DEPTH_TEST);
    glfwSetKeyCallback(m_window, key_callback);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return GL_TRUE;
}
