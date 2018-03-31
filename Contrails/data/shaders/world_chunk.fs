#version 330 core

#include "data/shaders/common/vertex.vs"

layout(location = 0) out vec4 color;

in Vertex vertex;

void main()
{
  color = vec4(vertex.color.rgb, 1);
}