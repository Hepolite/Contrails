#version 330 core

#include "data/shaders/common/camera.vs"
#include "data/shaders/common/model.vs"

layout(location = 0) out vec4 color;

in Vertex
{
	vec3 normal;
	vec3 uv;
	vec4 color;
	flat uint texture;
} vertex;

uniform sampler2DArray textureArraySampler;

vec3 calculateUVCoordinate()
{
	uint offset = vertex.texture & 0x0000FFFFu;
	uint meta = (vertex.texture & 0x00FF0000u) >> 16u;
	uint hash = (vertex.texture & 0xFF000000u) >> 24u ^ (137u * uint(vertex.uv.x)) ^ (2467u * uint(vertex.uv.y));
	
	return vertex.uv + vec3(0, 0, offset + hash % (meta + 1u));
}
vec4 calculateTextureColor()
{
	return texture(textureArraySampler, calculateUVCoordinate());
}
float calculateSideShadowFactor()
{
	const vec3 sunDirection = normalize(vec3(-5, -2, -12)); // TODO: Pass as uniform
	
	vec3 normal = vec3(model.transform * vec4(vertex.normal, 0.0));
	float dot = clamp(dot(-sunDirection, normal), -0.5, 1.0);
	
	return 0.8 + 0.2 * dot;
}
vec3 calculateLightColor()
{
	const vec3 sunlight = vec3(1.0, 1.0, 1.0); // TODO: Pass as uniform
	
	vec3 light = vertex.color.rgb + vertex.color.a * sunlight;
	light.r = clamp(light.r, 0.0, 1.0);
	light.g = clamp(light.g, 0.0, 1.0);
	light.b = clamp(light.b, 0.0, 1.0);
	return light * calculateSideShadowFactor();
}

void main()
{
	color = calculateTextureColor() * vec4(calculateLightColor(), 1);
}