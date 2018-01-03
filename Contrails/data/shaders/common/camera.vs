
layout (std140) uniform Camera
{
	mat4 proj;
	mat4 projInv;
	mat4 view;
	mat4 viewInv;
	mat4 projview;
	mat4 projviewInv;
} camera;
