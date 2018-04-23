
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

	m_projviewInv = glm::inverse(calculateProjectionMatrix() * calculateViewMatrix());
}
void render::scene::Camera::upload(float pt) const
{
	if (m_registry == nullptr)
		return;

	const auto proj = calculateProjectionMatrix(pt);
	const auto view = calculateViewMatrix(pt);
	const auto projView = proj * view;

	const auto & ubo = m_registry->get("Camera");
	ubo.set("proj", proj);
	ubo.set("projInv", glm::inverse(proj));
	ubo.set("view", view);
	ubo.set("viewInv", glm::inverse(view));
	ubo.set("projview", projView);
	ubo.set("projviewInv", glm::inverse(projView));
}

glm::mat4 render::scene::Camera::calculateProjectionMatrix(float pt) const
{
	const auto fov = math::lerp(m_oldFov, m_fov, pt);

	const glm::vec2 size = m_display == nullptr ? glm::vec2{ 1.0f, 1.0f } : m_display->getSize();
	return glm::perspective(glm::radians(fov), size.x / size.y, m_znear, m_zfar);
}
glm::mat4 render::scene::Camera::calculateViewMatrix(float pt) const
{
	const auto pos = math::lerp(m_oldPos, m_pos, pt);
	const auto rot = math::lerp(m_oldRot, m_rot, pt);
	const auto up = math::lerp(m_oldUp, m_up, pt);

	return glm::lookAt(pos, pos + math::cartesian(rot), up);
}

void render::scene::Camera::lookTowards(const glm::vec3 & target, bool snap)
{
	setRotation(math::spherical(target - m_pos), snap);
}
glm::vec3 render::scene::Camera::getLookVector(const glm::vec2 & mouseVector) const
{
	const auto far = m_projviewInv * glm::vec4{ mouseVector.x, mouseVector.y, 0.5f, 1.0f };
	const auto near = m_projviewInv * glm::vec4{ mouseVector.x, mouseVector.y, -0.5f, 1.0f };
	return glm::normalize(glm::vec3{ far / far.w } - glm::vec3{ near / near.w });
}
glm::vec2 render::scene::Camera::getMouseVector(const glm::vec2 mousePos) const
{
	const glm::vec2 size = m_display == nullptr ? glm::vec2{ 1.0f, 1.0f } : m_display->getSize();
	return 2.0f * glm::vec2{ mousePos.x, size.y - mousePos.y } / size - 1.0f;
}

void render::scene::Camera::setPosition(const glm::vec3 & pos, bool snap)
{
	m_oldPos = snap ? pos : m_oldPos;
	m_pos = pos;
}
void render::scene::Camera::setRotation(const glm::vec2 & rot, bool snap)
{
	m_oldRot = snap ? rot : m_oldRot;
	m_rot = rot;
}
void render::scene::Camera::setRotation(float yaw, float pitch, bool snap)
{
	setRotation({ yaw, pitch }, snap);
}
void render::scene::Camera::setUpVector(const glm::vec3 & up, bool snap)
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
