#version 330 core

//input data *passed from vertex shader*
in vec3 fragmentColor;

// Ouput data
out vec3 color;

void main()
{
	 //color = vec3(1,1,0);
	 color = fragmentColor;
}

