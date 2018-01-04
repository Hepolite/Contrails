
#include "Camera.h"

#include "util/Maths.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

void render::scene::Camera::process()
{
	m_oldPos = m_pos;
	m_oldRot = m_rot;
	m_oldUp = m_up;
	m_oldFov = m_fov;
}
void render::scene::Camera::upload(float dt) const
{
	const auto pos = math::lerp(m_oldPos, m_pos, dt);
	const auto rot = math::lerp(m_oldRot, m_rot, dt);
	const auto up = math::lerp(m_oldUp, m_up, dt);
	const float fov = math::lerp(m_oldFov, m_fov, dt);

	const glm::vec2 size{ 640.0f, 480.0f }; // { Core::getDisplay().getWidth(), Core::getDisplay().getHeight() };
	const auto proj = glm::perspective(glm::radians(fov), size.x / size.y, m_znear, m_zfar);
	const auto view = glm::lookAt(pos, pos + math::cartesian(rot), up);
	const auto projView = proj * view;
	m_projviewInv = glm::inverse(projView);

	/*const auto& cameraBlock = Core::getUniformBlockManager().get("Camera");
	cameraBlock.setField("proj", proj);
	cameraBlock.setField("projInv", glm::inverse(proj));
	cameraBlock.setField("view", view);
	cameraBlock.setField("viewInv", glm::inverse(view));
	cameraBlock.setField("projview", projView);
	cameraBlock.setField("projviewInv", m_projviewInv);*/
}


void render::scene::Camera::setPosition(const glm::vec3& pos, bool snap)
{
	m_oldPos = snap ? pos : m_oldPos;
	m_pos = pos;
}
void render::scene::Camera::setRotation(const glm::vec2& rot, bool snap)
{
	m_oldRot = snap ? rot : m_oldRot;
	m_rot = rot;
}
void render::scene::Camera::setRotation(float yaw, float pitch, bool snap)
{
	setRotation(glm::vec2{ yaw, pitch }, snap);
}
void render::scene::Camera::lookTowards(const glm::vec3& target, bool snap)
{
	setRotation(math::spherical(target - m_pos), snap);
}

void render::scene::Camera::setUpVector(const glm::vec3& up, bool snap)
{
	m_oldUp = snap ? up : m_oldUp;
	m_up = up;
}
void render::scene::Camera::setFOV(float fov, bool snap)
{
	m_oldFov = snap ? fov : m_oldFov;
	m_fov = fov;
}
void render::scene::Camera::setViewDistance(float znear, float zfar)
{
	m_znear = znear;
	m_zfar = zfar;
}

glm::vec3 render::scene::Camera::getWorldVector(const glm::vec2 & screenVector) const
{
	const glm::vec2 size{ 640.0f, 480.0f }; // { Core::getDisplay().getWidth(), Core::getDisplay().getHeight() };

	// Magic. DO NOT TOUCH!
	const auto v = 2.0f * screenVector / size - 1.0f;
	const auto far = m_projviewInv * glm::vec4{ v.x, -v.y, 0.5f, 1.0f };
	const auto near = m_projviewInv * glm::vec4{ v.x, -v.y, -0.5f, 1.0f };
	return glm::normalize(glm::vec3{ far / far.w } -glm::vec3{ near / near.w });
}
