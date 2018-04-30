
#include "CppUnitTest.h"

#include "editor/util/CameraHandler.h"
#include "logic/event/Events.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace editor
{
	namespace util
	{
		class CameraHandlerMock : public CameraHandler
		{
		public:
			inline auto isSetup() const { return m_setup; }

		private:
			virtual void setupListeners(logic::event::EventBus & bus) override final { m_setup = true; }

			bool m_setup = false;
		};

		TEST_CLASS(CameraHandlerTest)
		{
		public:
			TEST_METHOD(CameraHandler_injectEventBus)
			{
				logic::event::EventBus bus;
				CameraHandlerMock handler;
				handler.inject(bus);

				Assert::IsTrue(handler.isSetup());
			}
		};

		TEST_CLASS(CameraHandlerOrbitalTest)
		{
		public:
			CameraHandlerOrbitalTest()
			{
				m_handler.inject(m_bus);
				m_handler.inject(m_camera);
			}

			TEST_METHOD(CameraHandlerOrbital_dragWithoutClicking)
			{
				const auto pos = m_camera.getPosition();
				const auto rot = m_camera.getRotation();

				simulateMouseMove({ 4.0, 1.0f });

				Assert::AreEqual(pos, m_camera.getPosition());
				Assert::AreEqual(rot, m_camera.getRotation());
			}

			TEST_METHOD(CameraHandlerOrbital_rotateInPlace)
			{
				const auto pos = m_camera.getPosition();
				const auto rot = m_camera.getRotation();

				simulateKeyPress(ALLEGRO_KEY_LCTRL);
				simulateMousePress(ui::mouse::Button::MIDDLE);
				simulateMouseMove({ 5.0f, 4.0f });

				Assert::AreEqual(pos, m_camera.getPosition());
				Assert::AreNotEqual(rot, m_camera.getRotation());
			}
			TEST_METHOD(CameraHandlerOrbital_rotateAroundPoint)
			{
				const auto pos = m_camera.getPosition();
				const auto rot = m_camera.getRotation();

				simulateMousePress(ui::mouse::Button::MIDDLE);
				simulateMouseMove({ 5.0f, 4.0f });

				Assert::AreNotEqual(pos, m_camera.getPosition());
				Assert::AreNotEqual(rot, m_camera.getRotation());
			}

		private:
			void simulateMouseMove(const glm::vec2 & delta)
			{
				m_bus.post(logic::event::MouseMove{ {}, delta, {}, {} });
			}
			void simulateMousePress(ui::mouse::Button button)
			{
				m_bus.post(logic::event::MousePress{ button, 0.0f, {}, {} });
			}
			void simulateMouseRelease(ui::mouse::Button button)
			{
				m_bus.post(logic::event::MouseRelease{ button, 0.0f, {}, {} });
			}
			void simulateKeyPress(int key)
			{
				m_bus.post(logic::event::KeyPress{ key, 0u });
			}
			void simulateKeyRelease(int key)
			{
				m_bus.post(logic::event::KeyRelease{ key, 0u });
			}

			logic::event::EventBus m_bus;
			render::scene::Camera m_camera;
			CameraHandlerOrbital m_handler;
		};
	}
}