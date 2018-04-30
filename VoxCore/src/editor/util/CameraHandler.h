
#pragma once

#include "logic/event/EventBus.h"
#include "logic/event/EventListener.h"
#include "render/scene/Camera.h"

namespace editor
{
	namespace util
	{
		class CameraHandler
		{
		public:
			CameraHandler() = default;
			CameraHandler(const CameraHandler &) = delete;
			CameraHandler(CameraHandler &&) = delete;
			virtual ~CameraHandler() = default;

			CameraHandler & operator=(const CameraHandler &) = delete;
			CameraHandler & operator=(CameraHandler &&) = delete;

			inline void inject(logic::event::EventBus & bus) { setupListeners(bus); }
			inline void inject(render::scene::Camera & camera) { m_camera = &camera; }

		protected:
			virtual void setupListeners(logic::event::EventBus & bus) = 0;

			inline auto & getCamera() { return *m_camera; }

		private:
			render::scene::Camera * m_camera = nullptr;
		};

		class CameraHandlerOrbital : public CameraHandler
		{
		private:
			void handleRotation(const glm::vec2 & delta);
			void handleZooming(float zoom);

			virtual void setupListeners(logic::event::EventBus & bus) override final;

			logic::event::Listener m_mousePress;
			logic::event::Listener m_mouseRelease;
			logic::event::Listener m_mouseMove;
			logic::event::Listener m_keyPress;
			logic::event::Listener m_keyRelease;

			bool m_holdMouseButton = false;
			bool m_holdKeyPrimary = false;
			bool m_holdKeySecondary = false;

			float m_sensitivity = 1.0f;
			float m_distance = 25.0f;
		};
	}
}