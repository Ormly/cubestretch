#version 330 core

out vec4 color;

in vec3 colorFromVS;

void main()
{
	color = vec4(colorFromVS, 1.0);
}