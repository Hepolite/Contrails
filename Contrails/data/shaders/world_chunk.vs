#version 330 core

#include "data/shaders/common/camera.vs"
#include "data/shaders/common/model.vs"
#include "data/shaders/common/vertex.vs"

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec3 inUV;
layout(location = 3) in vec4 inColor;

out Vertex vertex;

void main()
{
  gl_Position = camera.projview * model.transform * vec4(inPosition, 1.0);
  
  vertex.normal = inNormal;
  vertex.uv = inUV; 
  vertex.color = inColor;
}