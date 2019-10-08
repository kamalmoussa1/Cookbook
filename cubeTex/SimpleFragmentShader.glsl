#version 330 core

//input data *passed from vertex shader*
in vec2 UV;

// Ouput data
out vec3 color;

uniform sampler2D textureSampler;

void main()
{
	 color = texture(textureSampler, UV).rgb;
}

