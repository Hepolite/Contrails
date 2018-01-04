
#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace render
{
	namespace scene
	{
		class Camera
		{
		public:
			void setPosition(const glm::vec3 & pos, bool snap = false);
			void setRotation(const glm::vec2 & rot, bool snap = false);
			void setRotation(float yaw, float pitch, bool snap = false);
			void lookTowards(const glm::vec3 & target, bool snap = false);

			void setUpVector(const glm::vec3 & up, bool snap = false);
			void setFOV(float fov, bool snap = false);
			void setViewDistance(float znear, float zfar);

			inline glm::vec3 getPosition() const { return m_pos; }
			inline glm::vec2 getRotation() const { return m_rot; }
			inline glm::vec3 getUpVector() const { return m_up; }
			inline float getFOV() const { return m_fov; }

			glm::vec3 getWorldVector(const glm::vec2 & screenVector) const;

			void process();
			void upload(float dt) const;

		private:
			glm::vec3 m_pos{}, m_oldPos{};
			glm::vec2 m_rot{}, m_oldRot{};
			glm::vec3 m_up{ 0.0f, 0.0f, 1.0f }, m_oldUp{ m_up };

			float m_fov = 70.0f, m_oldFov{ m_fov };

			float m_znear = 0.1f;
			float m_zfar = 15000.0f;

			mutable glm::mat4 m_projviewInv;
		};
	}
}