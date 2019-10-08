#version 330 core

// Ouput data
out vec4 outColor;
smooth in vec4 color;

uniform float time;

void main()
{

//  color = mix(vec4(1.0, 0.0, 0.0, 1.0),
//              vec4(0.0, 1.0, 0.0, 1.0), 0);
  float tt = mod(time, 5);
  outColor = mix(color, vec4(0.8, 0.5, 0.2, 1.0), tt);
}

