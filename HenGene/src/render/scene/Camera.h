
#pragma once

#include "render/uboRegistry.h"
#include "ui/Display.h"

#include <glm/mat4x4.hpp>

namespace render
{
	namespace scene
	{
		class Camera
		{
		public:
			Camera() = default;
			Camera(const Camera &) = delete;
			Camera(Camera &&) = delete;
			~Camera() = default;

			Camera & operator=(const Camera &) = delete;
			Camera & operator=(Camera &&) = delete;

			inline void inject(const uboRegistry & registry) { m_registry = &registry; }
			inline void inject(const ui::Display & display) { m_display = &display; }

			void process();
			void upload(float pt) const;

			void lookTowards(const glm::vec3 & target, bool snap = false);
			glm::vec3 getLookVector(const glm::vec2 & mouseVector = { 0.0f, 0.0f }) const;

			void setPosition(const glm::vec3 & pos, bool snap = false);
			void setRotation(const glm::vec2 & rot, bool snap = false);
			void setRotation(float yaw, float pitch, bool snap = false);
			void setUpVector(const glm::vec3 & up, bool snap = false);
			void setFOV(float fov, bool snap = false);
			void setViewDistance(float znear, float zfar);

			inline auto getPosition() const { return m_pos; }
			inline auto getRotation() const { return m_rot; }
			inline auto getUpVector() const { return m_up; }
			inline auto getFOV() const { return m_fov; }

			glm::vec2 getMouseVector(const glm::vec2 mousePos) const;

		private:
			glm::mat4 calculateProjectionMatrix(float pt = 0.0f) const;
			glm::mat4 calculateViewMatrix(float pt = 0.0f) const;

			const uboRegistry * m_registry = nullptr;
			const ui::Display * m_display = nullptr;

			glm::vec3 m_pos{}, m_oldPos{};
			glm::vec2 m_rot{}, m_oldRot{};
			glm::vec3 m_up{ 0.0f, 0.0f, 1.0f }, m_oldUp{ m_up };

			float m_fov = 70.0f, m_oldFov = m_fov;

			float m_znear = 0.1f;
			float m_zfar = 15000.0f;

			glm::mat4 m_projviewInv;
		};
	}
}