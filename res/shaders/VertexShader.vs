#version 330 core

layout(location = 0) in vec3 position;

uniform mat4 u_modelTransform;

void main()
{
    vec4 vertex = vec4(position, 1.0);
    gl_Position = u_modelTransform * vertex;
}

