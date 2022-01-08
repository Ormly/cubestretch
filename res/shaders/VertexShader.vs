#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertexColor;

out vec3 colorFromVS;

uniform mat4 u_modelTransform;

void main()
{
    vec4 vertex = vec4(position, 1.0);
    gl_Position = u_modelTransform * vertex;
    colorFromVS = vertexColor;
}

