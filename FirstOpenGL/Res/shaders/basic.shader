#shader vertex
#version 430

layout(location = 0) in  vec4 position;
layout(location = 1) in  vec2 texCoord;
out vec2 v_texCoord;

uniform mat4 u_MVP;

void main()
{
  gl_Position = position * u_MVP;
  v_texCoord = texCoord;
}

#shader fragment
#version 430

in vec2 v_texCoord;
layout(location=0) out vec4 fragColor;
uniform vec4 u_Color;
uniform sampler2D u_texture;

void main()
{
  vec4 texColor = texture(u_texture, v_texCoord)/* u_Color*/;
  fragColor = texColor;
}

