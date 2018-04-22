
#include "CppUnitTest.h"

#include "editor/Editor.h"
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

	private:
		setup::Context m_context;
	};
}