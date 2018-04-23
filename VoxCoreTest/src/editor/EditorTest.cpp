
#include "CppUnitTest.h"

#include "core/setup/SetupScripts.h"
#include "editor/Editor.h"
#include "logic/script/ScriptUtil.h"
#include "render/scene/renderers/RendererGeneric.h"

#include "Setup.h"

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
		TEST_METHOD(Editor_injectScene)
		{
			core::scene::Scene scene;
			scene.registerRenderers<render::scene::RendererGeneric>();
			{
				EditorMock editor;
				editor.inject(scene);
				scene.process(0.0_s, 0.05_s);
				scene.render(0.0_s, 0.05_s, 0.0f);

				Assert::IsTrue(scene.hasEntity(0u));
				Assert::IsTrue(editor.isProcessed());
				Assert::IsTrue(editor.isRendered());
			}
			Assert::IsFalse(scene.hasEntity(0u));
		}

		TEST_METHOD(Editor_injectGui)
		{
			ui::gui::Gui gui;
			EditorMock editor;
			editor.inject(gui);
			Assert::IsTrue(gui.getScript().execute("EDITOR.getShape()"));
		}

		TEST_METHOD(Editor_performActionOnMouseClick)
		{
			ui::gui::Gui gui;
			logic::event::EventBus bus;
			logic::script::Script & script = gui.getScript();
			script.execute("global value = 0;");
			script.execute("global MOUSE_BUTTON_LEFT = 1;");
			script.execute("global MOUSE_BUTTON_MIDDLE = 2;");
			script.execute("global MOUSE_BUTTON_RIGHT = 3;");
			script.execute("def action(type) { value = type; }");

			EditorMock editor;
			editor.inject(gui);
			editor.inject(bus);

			bus.post<logic::event::MouseRelease>({ ui::mouse::Button::LEFT, 0.0f,{},{} });
			Assert::AreEqual(0, logic::script::util::get<int>(script, "value"));

			editor.validateCursor();

			bus.post<logic::event::MouseRelease>({ ui::mouse::Button::LEFT, 0.0f, {}, {} });
			Assert::AreEqual(1, logic::script::util::get<int>(script, "value"));
			bus.post<logic::event::MouseRelease>({ ui::mouse::Button::MIDDLE, 0.0f, {}, {} });
			Assert::AreEqual(2, logic::script::util::get<int>(script, "value"));
			bus.post<logic::event::MouseRelease>({ ui::mouse::Button::RIGHT, 0.0f, {}, {} });
			Assert::AreEqual(3, logic::script::util::get<int>(script, "value"));
		}

	private:
		setup::Context m_context;
	};
}