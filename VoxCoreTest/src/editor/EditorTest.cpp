
#include "CppUnitTest.h"

#include "core/setup/SetupScripts.h"
#include "editor/Editor.h"
#include "logic/script/ScriptUtil.h"
#include "render/scene/renderers/RendererGeneric.h"

#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace editor
{
	class EditorMock : public Editor
	{
	public:
		virtual void process(const Time & t, const Time & dt) override final
		{
			m_processed = true;
		}
		virtual void render(const render::RenderContext & context, const Time & t, const Time & dt) const override final
		{
			m_rendered = true;
		}

		inline void validateCursor() { getCursor().setValidPos(true); }

		inline bool isProcessed() const { return m_processed; }
		inline bool isRendered() const { return m_rendered; }

	private:
		bool m_processed = false;
		mutable bool m_rendered = false;
	};

	TEST_CLASS(EditorTest)
	{
	public:
		EditorTest()
		{
			m_scene.registerRenderers<render::scene::RendererGeneric>();

			m_editor.inject(m_scene);
			m_editor.inject(m_gui);
			m_editor.inject(m_bus);
		}

		TEST_METHOD(Editor_initializeProcessingAndRendering)
		{
			m_scene.process(0.0_s, 0.05_s);
			m_scene.render(0.0_s, 0.05_s, 0.0f);

			Assert::IsTrue(m_editor.isProcessed());
			Assert::IsTrue(m_editor.isRendered());
		}
		TEST_METHOD(Editor_initializeScripts)
		{
			Assert::IsTrue(m_gui.getScript().execute("EDITOR.getShape()"));
		}
		TEST_METHOD(Editor_initializeCameraHandler)
		{
			auto & camera = m_scene.getCamera(render::scene::CameraType::NORMAL);
			const auto pos = camera.getPosition();
			const auto rot = camera.getRotation();

			m_bus.post<logic::event::MousePress>({ ui::mouse::Button::MIDDLE, 0.0f, {}, {} });
			m_bus.post<logic::event::MouseMove>({ {}, { 4.0f, 1.0f }, {}, {} });

			Assert::AreNotEqual(pos, camera.getPosition());
			Assert::AreNotEqual(rot, camera.getRotation());
		}

		TEST_METHOD(Editor_performActionOnMouseClick)
		{
			auto & script = m_gui.getScript();
			script.execute("global value = 0;");
			script.execute("global MOUSE_BUTTON_LEFT = 1;");
			script.execute("global MOUSE_BUTTON_MIDDLE = 2;");
			script.execute("global MOUSE_BUTTON_RIGHT = 3;");
			script.execute("def action(type) { value = type; }");

			m_bus.post<logic::event::MouseRelease>({ ui::mouse::Button::LEFT, 0.0f, {}, {} });
			Assert::AreEqual(0, logic::script::util::get<int>(script, "value"));

			m_editor.validateCursor();

			m_bus.post<logic::event::MouseRelease>({ ui::mouse::Button::LEFT, 0.0f, {}, {} });
			Assert::AreEqual(1, logic::script::util::get<int>(script, "value"));
			m_bus.post<logic::event::MouseRelease>({ ui::mouse::Button::MIDDLE, 0.0f, {}, {} });
			Assert::AreEqual(2, logic::script::util::get<int>(script, "value"));
			m_bus.post<logic::event::MouseRelease>({ ui::mouse::Button::RIGHT, 0.0f, {}, {} });
			Assert::AreEqual(3, logic::script::util::get<int>(script, "value"));
		}

	private:
		core::scene::Scene m_scene;
		logic::event::EventBus m_bus;
		ui::gui::Gui m_gui;

		EditorMock m_editor;

		setup::Context m_context;
	};
}