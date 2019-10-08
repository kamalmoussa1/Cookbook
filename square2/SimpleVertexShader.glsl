#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 vertexPosition;
layout(location = 1) in vec4 vertexColor;

uniform vec3 offset;
smooth out vec4 color;

void main()
{
  color = vertexColor;
  gl_Position= vertexPosition + vec4(offset.x, offset.y, offset.z, 1.0);
}

