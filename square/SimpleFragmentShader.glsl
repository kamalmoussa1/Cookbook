#version 330 core

// Ouput data
out vec4 color;

void main()
{
  // Output color = red
  color = mix(vec4(1.0, 0.0, 0.0, 1.0),
              vec4(0.0, 1.0, 0.0, 1.0), gl_FragCoord.y/500.0);
}

