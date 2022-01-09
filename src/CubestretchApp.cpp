#include "CubestretchApp.h"
#include <iostream>
#include <array>

#include "glm/gtc/matrix_transform.hpp"

namespace
{
    GLfloat halfSideCubeLength = 3.0f;
    GLfloat edgeStripWidth = 0.25f;
    GLuint lastCubeID = 0;

    glm::vec3 cubeColor({0.541f, 0.011f, 0.011f}); //blood red
    glm::vec3 selectedCubeColor({0.003f, 0.266f, 0.129f}); //forest green
    glm::vec3 edgeStripColor({0.647f, 0.486f, 0.0f}); //darker gold

    GLboolean SHIFTIsDown;
    GLboolean keyStateWRepeat = false;
    GLboolean keyStateARepeat = false;
    GLboolean keyStateSRepeat = false;
    GLboolean keyStateDRepeat = false;
    GLboolean keyStateESCAPERepeat = false;
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

    while (!glfwWindowShouldClose(m_window))
    {
        GLdouble currentTime = glfwGetTime();
        m_deltaTime += (currentTime - m_previousTime) / m_limitFPS;
        m_previousTime = currentTime;

        while (m_deltaTime >= 1.0)
        {
            glfwPollEvents();
            checkInput();
            m_deltaTime--;
        }

        render();
        glfwSwapBuffers(m_window);
    }

    glfwTerminate();

    return 0;
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

void render()
{
    m_renderer.clear();

    m_modelTransform = m_projection * m_camera->getWorldToViewMatrix() * m_translation * m_rotation;
    m_shaders->setUniformMat4f("u_modelTransform", m_modelTransform);

    for(Cube* cube : m_cubes)
    {
        if(m_state == SELECTING && cube->getID() == m_selectedCubeID)
            cube->setEdgeStripColor(selectedCubeColor);
        else
            cube->setEdgeStripColor(edgeStripColor);

        if(m_state == BUILDING && cube->getID() == m_selectedCubeID)
            cube->setCubeColor(selectedCubeColor);
        else
            cube->setCubeColor(cubeColor);

        m_renderer.draw(*(cube->getVertexArray()), *(cube->getIndexBuffer()), *m_shaders);
    }
}

void checkInput()
{
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


    //TODO move Key input handling into separate class
    int keyStateW = glfwGetKey(m_window, GLFW_KEY_W);
    int keyStateA = glfwGetKey(m_window, GLFW_KEY_A);
    int keyStateS = glfwGetKey(m_window, GLFW_KEY_S);
    int keyStateD = glfwGetKey(m_window, GLFW_KEY_D);
    int keyStateESCAPE = glfwGetKey(m_window, GLFW_KEY_ESCAPE);
    int keyStateB = glfwGetKey(m_window, GLFW_KEY_B);
    int keyStateSHIFT = glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT);
    int keyStateQ = glfwGetKey(m_window, GLFW_KEY_Q);
    int keyStateENTER = glfwGetKey(m_window, GLFW_KEY_ENTER);
    int keyStateSPACE = glfwGetKey(m_window, GLFW_KEY_SPACE);
    int keyStateCTRL = glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL);

    if (keyStateQ == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);

    SHIFTIsDown = (keyStateSHIFT == GLFW_PRESS);

    if(m_state == NONE)
    {
        if(keyStateB == GLFW_PRESS)
            m_state = SELECTING;

        if(keyStateW == GLFW_PRESS)
            m_camera->moveForward();

        if(keyStateS == GLFW_PRESS)
            m_camera->moveBackward();

        if(keyStateA == GLFW_PRESS)
            m_camera->strafeLeft();

        if(keyStateD == GLFW_PRESS)
            m_camera->strafeRight();

        if(keyStateSPACE == GLFW_PRESS)
            m_camera->moveUp();

        if(keyStateCTRL == GLFW_PRESS)
            m_camera->moveDown();
    }

    Cube* selectedCube = getCubeFromID(m_selectedCubeID);
    GLint neighborID;

    bool keyStateWIsValid = !keyStateWRepeat && keyStateW == GLFW_PRESS;
    bool keyStateAIsValid = !keyStateARepeat && keyStateA == GLFW_PRESS;
    bool keyStateSIsValid = !keyStateSRepeat && keyStateS == GLFW_PRESS;
    bool keyStateDIsValid = !keyStateDRepeat && keyStateD == GLFW_PRESS;

    if(m_state == SELECTING)
    {
        if(!keyStateESCAPERepeat && keyStateESCAPE == GLFW_PRESS)
        {
            keyStateESCAPERepeat = true;
            m_state = NONE;
        }
        else if(keyStateESCAPE == GLFW_RELEASE)
            keyStateESCAPERepeat = false;

        if(keyStateENTER == GLFW_PRESS)
            m_state = BUILDING;

        if(keyStateWIsValid)
        {
            keyStateWRepeat = true;
            neighborID = SHIFTIsDown ? selectedCube->getBackNeighbor() : selectedCube->getUpNeighbor();
            if(neighborID > -1)
                m_selectedCubeID = neighborID;
        }
        else if(keyStateW == GLFW_RELEASE)
            keyStateWRepeat = false;

        if(keyStateAIsValid)
        {
            keyStateARepeat = true;
            neighborID = selectedCube->getLeftNeighbor();
            if(neighborID > -1)
                m_selectedCubeID = neighborID;
        }
        else if(keyStateA == GLFW_RELEASE)
            keyStateARepeat = false;

        if(keyStateSIsValid)
        {
            keyStateSRepeat = true;
            neighborID = SHIFTIsDown ? selectedCube->getFrontNeighbor() : selectedCube->getDownNeighbor();
            if(neighborID > -1)
                m_selectedCubeID = neighborID;
        }
        else if(keyStateS == GLFW_RELEASE)
            keyStateSRepeat = false;

        if(keyStateDIsValid)
        {
            keyStateDRepeat = true;
            neighborID = selectedCube->getRightNeighbor();
            if(neighborID > -1)
                m_selectedCubeID = neighborID;
        }
        else if(keyStateD == GLFW_RELEASE)
            keyStateDRepeat = false;

    }

    if(m_state == BUILDING)
    {
        if(!keyStateESCAPERepeat && keyStateESCAPE == GLFW_PRESS)
        {
            keyStateESCAPERepeat = true;
            m_state = SELECTING;
        }
        else if(keyStateESCAPE == GLFW_RELEASE)
            keyStateESCAPERepeat = false;

        if(keyStateWIsValid)
        {
            keyStateWRepeat = true;
            neighborID = SHIFTIsDown ? selectedCube->getBackNeighbor() : selectedCube->getUpNeighbor();
            if(neighborID == -1)
                createCube(selectedCube, SHIFTIsDown ? BACK : UP);
        }
        else if(keyStateW == GLFW_RELEASE)
            keyStateWRepeat = false;

        if(keyStateAIsValid)
        {
            keyStateARepeat = true;
            neighborID = selectedCube->getLeftNeighbor();
            if(neighborID == -1)
                createCube(selectedCube, LEFT);
        }
        else if(keyStateA == GLFW_RELEASE)
            keyStateARepeat = false;

        if(keyStateSIsValid)
        {
            keyStateSRepeat = true;
            neighborID = SHIFTIsDown ? selectedCube->getFrontNeighbor() : selectedCube->getDownNeighbor();
            if(neighborID == -1)
                createCube(selectedCube, SHIFTIsDown ? FRONT : DOWN);
        }
        else if(keyStateS == GLFW_RELEASE)
            keyStateSRepeat = false;

        if(keyStateDIsValid)
        {
            keyStateDRepeat = true;
            neighborID = selectedCube->getRightNeighbor();
            if(neighborID == -1)
                createCube(selectedCube, RIGHT);
        }
        else if(keyStateD == GLFW_RELEASE)
            keyStateDRepeat = false;
    }
}

void initializeOriginCube()
{
    std::array<GLint, 6> neighbors{};
    neighbors.fill(-1);
    glm::vec3 originCubeCenter = {0.0f, 0.0f, 0.0f};
    Cube* originCube = new Cube(originCubeCenter, halfSideCubeLength, neighbors, cubeColor, lastCubeID++, edgeStripWidth, edgeStripColor);
    m_cubes.push_back(originCube);

    m_selectedCubeID = originCube->getID();
}

GLuint createCube(const Cube* sourceCube, Direction direction)
{
    glm::vec3 cubeCenter;
    glm::vec3 sourceCubeCenter = sourceCube->getCenter();
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

    std::array<GLint, 6> neighbors = calculateAndSetNeighbors(cubeCenter);
    cubeToAdd = new Cube(cubeCenter, halfSideCubeLength, neighbors, cubeColor, lastCubeID++, edgeStripWidth, edgeStripColor);
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

        if(cubeCenter.y == currentCubeCenter.y && cubeCenter.z == currentCubeCenter.z)
        {
            if((cubeCenter.x + halfSideCubeLength * 2) == currentCubeCenter.x)
            {
                neighbors.at(3) = currentCubeID;
                cube->addNeighbor(lastCubeID, LEFT);
            }

            if((cubeCenter.x - halfSideCubeLength * 2) == currentCubeCenter.x)
            {
                neighbors.at(2) = currentCubeID;
                cube->addNeighbor(lastCubeID, RIGHT);
            }
        }

        if(cubeCenter.x == currentCubeCenter.x && cubeCenter.z == currentCubeCenter.z)
        {
            if((cubeCenter.y + halfSideCubeLength * 2) == currentCubeCenter.y)
            {
                neighbors.at(0) = currentCubeID;
                cube->addNeighbor(lastCubeID, DOWN);
            }

            if((cubeCenter.y - halfSideCubeLength * 2) == currentCubeCenter.y)
            {
                neighbors.at(1) = currentCubeID;
                cube->addNeighbor(lastCubeID, UP);
            }
        }

        if(cubeCenter.x == currentCubeCenter.x && cubeCenter.y == currentCubeCenter.y)
        {
            if((cubeCenter.z + halfSideCubeLength * 2) == currentCubeCenter.z)
            {
                neighbors.at(4) = currentCubeID;
                cube->addNeighbor(lastCubeID, BACK);
            }

            if((cubeCenter.z - halfSideCubeLength * 2) == currentCubeCenter.z)
            {
                neighbors.at(5) = currentCubeID;
                cube->addNeighbor(lastCubeID, FRONT);
            }
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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    return GL_TRUE;
}
