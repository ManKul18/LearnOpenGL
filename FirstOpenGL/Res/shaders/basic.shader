#shader vertex
#version 430 

layout ( location=0 ) in  vec4 in_Position;

void main()
{
  gl_Position = in_Position;
}

#shader fragment
#version 430

layout(location=0) out vec4 fragColor;
uniform vec4 u_Color;

void main()
{
  fragColor = u_Color;
}

