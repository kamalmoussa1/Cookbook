#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 texCoord;

out vec3 fragmentColor;
out vec2 fregmentTexCoord;

uniform mat4 MVP;

void main()
{
  gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0);
	fragmentColor = vertexColor;
	fregmentTexCoord = texCoord;
}

