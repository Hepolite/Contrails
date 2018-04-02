#version 330 core

layout(location = 0) out vec4 color;

in Vertex
{
	vec3 normal;
	vec3 uv;
	vec4 color;
  float texture;
} vertex;

uniform sampler2DArray textureArraySampler;

vec4 calculateTextureColor()
{
  vec3 sunlight = vec3(1.0, 1.0, 1.0);
  
  vec3 light = vertex.color.rgb + vertex.color.a * sunlight;
  light.r = clamp(light.r, 0.0, 1.0);
	light.g = clamp(light.g, 0.0, 1.0);
	light.b = clamp(light.b, 0.0, 1.0);
  
  vec4 color = texture(textureArraySampler, vertex.uv + vec3(0, 0, vertex.texture));
  return color * vec4(light, 1);
}

void main()
{
  color = calculateTextureColor();
}