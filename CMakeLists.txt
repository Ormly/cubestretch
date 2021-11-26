cmake_minimum_required(VERSION 3.20)
project(cubestretch)

find_package(OpenGL REQUIRED)
message(STATUS "Found OpenGL")

set(CMAKE_CXX_STANDARD 14)

add_executable(cubestretch CubestretchApp.cpp)

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
