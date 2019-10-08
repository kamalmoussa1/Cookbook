#version 330 core

//input data *passed from vertex shader*
in vec3 fragmentColor;
in vec2 fregmentTexCoord;

// Ouput data
out vec4 color;

uniform sampler2D texSampler1;
uniform sampler2D texSampler2;

void main()
{
	 //color = vec3(1,1,0);
	 color = vec4(fragmentColor, 1.0);

	  // 0.2 will return 80% of the first input color and 20% of the second input color
//	  color = mix(texture(texSampler1, fregmentTexCoord), texture(texSampler2, fregmentTexCoord), 2.0);
//	  color = texture(texSampler1, fregmentTexCoord);

}

