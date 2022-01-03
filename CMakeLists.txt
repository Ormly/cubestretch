cmake_minimum_required(VERSION 3.20)
project(cubestretch)

find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL")

set(CMAKE_CXX_STANDARD 14)

add_executable(cubestretch
               src/CubestretchApp.h
               src/CubestretchApp.cpp
               src/renderer/VertexBuffer.h
               src/renderer/VertexBuffer.cpp
               src/renderer/IndexBuffer.h
               src/renderer/IndexBuffer.cpp
               src/renderer/VertexArray.cpp
               src/renderer/VertexArray.h
               src/renderer/VertexBufferLayout.cpp
               src/renderer/VertexBufferLayout.h
               src/renderer/Renderer.cpp
               src/renderer/Renderer.h
               src/renderer/Shaders.cpp
               src/renderer/Shaders.h
               res/shaders/FragmentShader.fs
               res/shaders/VertexShader.vs
               src/objects/Rectangle.h
               src/objects/Rectangle.cpp
               src/objects/Cube.cpp
               src/objects/Cube.h
               src/objects/CubeFace.cpp
               src/objects/CubeFace.h)

# GLM
find_package(GLM REQUIRED)
message(STATUS "Found GLM")

# GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3")

# GLEW
find_package(GLEW REQUIRED)
message(STATUS "Found GLEW")

set(INCLUDE_DIRS ${OPENGL_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
target_include_directories(cubestretch PUBLIC ${INCLUDE_DIRS})
message(STATUS "Included directories")

link_libraries("-static")
set(LIBRARIES glfw3 OpenGL::GL glm GLEW::GLEW)
target_link_libraries(cubestretch ${LIBRARIES})
message(STATUS "Linked libraries")
