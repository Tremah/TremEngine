#type vertex
#version 460 core
layout (location=0) in vec4 inPos;
layout (location=1) in vec4 inColor;

uniform mat4 uMvp;

out vec4 vertexColor;

void main()
{
  gl_Position  = uMvp * inPos;
  vertexColor  = inColor;
}

#type fragment
#version 460 core

in vec4 vertexColor;
out vec4 color;

void main()
{
  color = vertexColor;
}