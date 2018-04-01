#version 330 core

layout(location = 0) out vec4 color;

in Vertex
{
	vec3 normal;
	vec3 uv;
	vec4 color;
} vertex;

uniform sampler2DArray textureArraySampler;

void main()
{
  color = texture(textureArraySampler, vertex.uv) * vec4(vertex.color.rgb, 1.0);
}