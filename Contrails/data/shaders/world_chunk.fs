#version 330 core

layout(location = 0) out vec4 color;

in Vertex
{
	vec3 normal;
	vec3 uv;
	vec4 color;
} vertex;

void main()
{
  color = vec4(vertex.color.rgb, 1);
}