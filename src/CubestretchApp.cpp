#include "CubestretchApp.h"
#include <iostream>
#include <array>

#include "glm/gtc/matrix_transform.hpp"

namespace
{
    GLboolean isSHIFTDown;
    GLfloat halfSideCubeLength = 3.0f;
    GLuint lastCubeID = 0;
    glm::vec4 cubeColor({1.0f, 1.0f, 1.0f, 1.0f});
    GLuint waitTime = 5;
    GLuint waitTimer = waitTime;

    GLboolean keyWRepeat = false;
    GLboolean keyARepeat = false;
    GLboolean keySRepeat = false;
    GLboolean keyDRepeat = false;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main()
{
    m_windowWidth = 1600.0f;
    m_windowHeight = 1200.0f;

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
    //glfwSetCursorPos(m_window, m_windowWidth / 2, m_windowHeight / 2);
    checkInput();
}

void checkInput()
{
    int keyState;
    double cursorX, cursorY;
    glfwGetCursorPos(m_window, &cursorX, &cursorY);

    int mouseButtonState = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
    if(mouseButtonState == GLFW_PRESS)
        m_mouse->setState(PRESSED);
    else
        m_mouse->setState(RELEASED);

    m_mouse->setCurrentPosition(glm::vec2(cursorX, cursorY));
    if(m_mouse->getState() == RELEASED)
        m_camera->updateDirection(m_mouse->getPositionDelta());

    int keyStateW, keyStateA, keyStateS, keyStateD;
    keyStateW = glfwGetKey(m_window, GLFW_KEY_W);
    keyStateA = glfwGetKey(m_window, GLFW_KEY_A);
    keyStateS = glfwGetKey(m_window, GLFW_KEY_S);
    keyStateD = glfwGetKey(m_window, GLFW_KEY_D);

    keyState = glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT);
    isSHIFTDown = keyState == GLFW_PRESS;

    keyState = glfwGetKey(m_window, GLFW_KEY_Q);
    if (keyState == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);


    if(m_state == NONE)
    {
        keyState = glfwGetKey(m_window, GLFW_KEY_B);
        if(keyState == GLFW_PRESS)
            m_state = BUILDING;

        if(keyStateW == GLFW_PRESS)
            m_camera->moveForward();

        if(keyStateS == GLFW_PRESS)
            m_camera->moveBackward();

        if(keyStateA == GLFW_PRESS)
            m_camera->strafeLeft();

        if(keyStateD == GLFW_PRESS)
            m_camera->strafeRight();

        keyState = glfwGetKey(m_window, GLFW_KEY_SPACE);
        if(keyState == GLFW_PRESS)
            m_camera->moveUp();

        keyState = glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL);
        if(keyState == GLFW_PRESS)
            m_camera->moveDown();
    }

    if(m_state == BUILDING)
    {
        keyState = glfwGetKey(m_window, GLFW_KEY_ESCAPE);
        if(keyState == GLFW_PRESS)
            m_state = NONE;

        if(!keyWRepeat && !isSHIFTDown && keyStateW == GLFW_PRESS)
        {
            keyWRepeat = true;
            Cube* selectedCube = getCubeFromID(m_selectedCubeID);
            //TODO check for nullptr
            if(selectedCube->getUpNeighbor() == -1)
                createCube(selectedCube, UP);
        }
        else if(keyStateW == GLFW_RELEASE)
            keyWRepeat = false;

        if(!keyWRepeat && isSHIFTDown && keyStateW == GLFW_PRESS)
        {
            keyWRepeat = true;
            Cube* selectedCube = getCubeFromID(m_selectedCubeID);
            //TODO check for nullptr
            if(selectedCube->getBackNeighbor() == -1)
                createCube(selectedCube, BACK);
        }
        else if(keyStateW == GLFW_RELEASE)
            keyWRepeat = false;

        if(!keyARepeat && keyStateA == GLFW_PRESS)
        {
            keyARepeat = true;
            Cube* selectedCube = getCubeFromID(m_selectedCubeID);
            //TODO check for nullptr
            if(selectedCube->getLeftNeighbor() == -1)
                createCube(selectedCube, LEFT);
        }
        else if(keyStateA == GLFW_RELEASE)
            keyARepeat = false;

        if(!keySRepeat && !isSHIFTDown && keyStateS == GLFW_PRESS)
        {
            keySRepeat = true;
            Cube* selectedCube = getCubeFromID(m_selectedCubeID);
            //TODO check for nullptr
            if(selectedCube->getDownNeighbor() == -1)
                createCube(selectedCube, DOWN);
        }
        else if(keyStateS == GLFW_RELEASE)
            keySRepeat = false;

        if(!keySRepeat && isSHIFTDown && keyStateS == GLFW_PRESS)
        {
            keySRepeat = true;
            Cube* selectedCube = getCubeFromID(m_selectedCubeID);
            //TODO check for nullptr
            if(selectedCube->getFrontNeighbor() == -1)
                createCube(selectedCube, FRONT);
        }
        else if(keyStateS == GLFW_RELEASE)
            keySRepeat = false;

        if(!keyDRepeat && keyStateD == GLFW_PRESS)
        {
            keyDRepeat = true;
            Cube* selectedCube = getCubeFromID(m_selectedCubeID);
            //TODO check for nullptr
            if(selectedCube->getRightNeighbor() == -1)
                createCube(selectedCube, RIGHT);
        }
        else if(keyStateD == GLFW_RELEASE)
            keyDRepeat = false;
    }

    std::cout << "State: " << ((m_state == NONE) ? "None" : ((m_state == BUILDING) ? "Building" : "Selecting")) << std::endl;
    //std::cout << "A: " << ((keyStateA == GLFW_PRESS) ? "pressed, " : "not pressed, ") << ((keyStateA == GLFW_RELEASE) ? "released, " : "not released, ") << ((keyStateA == GLFW_REPEAT) ? "repeat" : "not repeat") << std::endl;
}

GLboolean wait()
{
    if(waitTimer > 0)
    {
        waitTimer--;
        return true;
    }
    else
    {
        waitTimer = waitTime;
        return false;
    }
}

void render()
{
    m_renderer.clear();

    m_modelTransform = m_projection * m_camera->getWorldToViewMatrix() * m_translation * m_rotation;
    m_shaders->setUniformMat4f("u_modelTransform", m_modelTransform);

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

    m_camera = new Camera();
    m_mouse = new MouseInput();

    m_identity = glm::mat4(1.0f);
    m_translation = glm::translate(m_identity, glm::vec3(0.0f, 0.0f, -40.0f));
    m_rotation = m_identity;
    m_projection = glm::perspective(glm::radians(60.0f), m_windowWidth / m_windowHeight, 0.1f, 200.0f);

    m_limitFPS = 1.0 / 60.0;
    m_previousTime = glfwGetTime();
    m_deltaTime = 0;

    m_state = NONE;
}

void initializeOriginCube()
{
    std::array<GLint, 6> neighbors{};
    neighbors.fill(-1);
    glm::vec3 originCubeCenter = {0.0f, 0.0f, 0.0f};
    //glm::vec3 originCubeCenter = {m_windowWidth / 2, m_windowHeight / 2, -1.0f};
    Cube* originCube = new Cube(originCubeCenter, halfSideCubeLength, neighbors, cubeColor, lastCubeID++);
    m_cubes.push_back(originCube);

    m_selectedCubeID = originCube->getID();
    m_previewCube = nullptr;
}

GLuint createCube(const Cube* sourceCube, Direction direction)
{
    glm::vec3 cubeCenter;
    glm::vec3 sourceCubeCenter = sourceCube->getCenter();
    std::array<GLint, 6> neighbors{};
    Cube* cubeToAdd;
    GLfloat cubeSideLength = halfSideCubeLength * 2;

    switch(direction)
    {
        case LEFT:
            cubeCenter = {sourceCubeCenter.x - cubeSideLength, sourceCubeCenter.y, sourceCubeCenter.z};
            break;
        case RIGHT:
            cubeCenter = {sourceCubeCenter.x + cubeSideLength, sourceCubeCenter.y, sourceCubeCenter.z};
            break;
        case UP:
            cubeCenter = {sourceCubeCenter.x, sourceCubeCenter.y + cubeSideLength, sourceCubeCenter.z};
            break;
        case DOWN:
            cubeCenter = {sourceCubeCenter.x, sourceCubeCenter.y - cubeSideLength, sourceCubeCenter.z};;
            break;
        case FRONT:
            cubeCenter = {sourceCubeCenter.x, sourceCubeCenter.y, sourceCubeCenter.z + cubeSideLength};
            break;
        case BACK:
            cubeCenter = {sourceCubeCenter.x, sourceCubeCenter.y, sourceCubeCenter.z - cubeSideLength};
            break;
    }

    neighbors = calculateAndSetNeighbors(cubeCenter);
    cubeToAdd = new Cube(cubeCenter, halfSideCubeLength, neighbors, cubeColor, lastCubeID++);
    m_cubes.push_back(cubeToAdd);

    m_selectedCubeID = cubeToAdd->getID();

    return cubeToAdd->getID();
}

std::array<GLint, 6> calculateAndSetNeighbors(glm::vec3 cubeCenter)
{
    glm::vec3 currentCubeCenter;
    std::array<GLint, 6> neighbors{};
    neighbors.fill(-1);

    for(Cube* cube : m_cubes)
    {
        currentCubeCenter = cube->getCenter();
        GLuint currentCubeID = cube->getID();
        if((cubeCenter.x + halfSideCubeLength * 2) == currentCubeCenter.x && (cubeCenter.y == currentCubeCenter.y && cubeCenter.z == currentCubeCenter.z))
        {
            neighbors.at(3) = currentCubeID;
            cube->addNeighbor(lastCubeID, LEFT);
        }

        if((cubeCenter.x - halfSideCubeLength * 2) == currentCubeCenter.x && (cubeCenter.y == currentCubeCenter.y && cubeCenter.z == currentCubeCenter.z))
        {
            neighbors.at(2) = currentCubeID;
            cube->addNeighbor(lastCubeID, RIGHT);
        }

        if((cubeCenter.y + halfSideCubeLength * 2) == currentCubeCenter.y && (cubeCenter.x == currentCubeCenter.x && cubeCenter.z == currentCubeCenter.z))
        {
            neighbors.at(0) = currentCubeID;
            cube->addNeighbor(lastCubeID, DOWN);
        }

        if((cubeCenter.y - halfSideCubeLength * 2) == currentCubeCenter.y && (cubeCenter.x == currentCubeCenter.x && cubeCenter.z == currentCubeCenter.z))
        {
            neighbors.at(1) = currentCubeID;
            cube->addNeighbor(lastCubeID, UP);
        }

        if((cubeCenter.z + halfSideCubeLength * 2) == currentCubeCenter.x && (cubeCenter.y == currentCubeCenter.y && cubeCenter.z == currentCubeCenter.z))
        {
            neighbors.at(4) = currentCubeID;
            cube->addNeighbor(lastCubeID, BACK);
        }

        if((cubeCenter.z - halfSideCubeLength * 2) == currentCubeCenter.x && (cubeCenter.x == currentCubeCenter.x && cubeCenter.y == currentCubeCenter.y))
        {
            neighbors.at(5) = currentCubeID;
            cube->addNeighbor(lastCubeID, FRONT);
        }
    }

    return neighbors;
}

Cube* getCubeFromID(GLuint cubeID)
{
    for(Cube* cube : m_cubes)
        if(cube->getID() == cubeID)
            return cube;

    return nullptr;
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

    glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glEnable(GL_DEPTH_TEST);
    glfwFocusWindow(m_window);
    //glfwSetCursorPosCallback(m_window, cursor_position_callback);
    //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return GL_TRUE;
}
