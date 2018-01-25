#version 330 core

#include "data/shaders/common/camera.vs"
#include "data/shaders/common/model.vs"

layout(location = 0) in vec3 inPosition;

void main()
{
  gl_Position = camera.projview * model.transform * vec4(inPosition, 1.0);
}