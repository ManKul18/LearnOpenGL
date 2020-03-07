#shader vertex
#version 430 

layout ( location=0 ) in  vec4 in_Position;

void main()
{
  gl_Position = in_Position;
}

#shader fragment
#version 430

out vec4 fragColor;

void main()
{
  fragColor = vec4(0.8, 0.1, 0.1, 1.0); 
}

