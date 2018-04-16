
#pragma once

#include "ui/gui/detail/Widget.h"
#include "ui/gui/detail/Widgets.h"

namespace ui
{
	namespace gui
	{
		class Renderer
		{
		public:
			Renderer() = delete;
			Renderer(Widget & widget);
			Renderer(const Renderer &) = default;
			Renderer(Renderer &&) = default;
			virtual ~Renderer() = default;

			Renderer & operator=(const Renderer &) = default;
			Renderer & operator=(Renderer &&) = default;
			inline void operator()(const glm::vec2 & pos) const { onRender(pos); }

			virtual void onRender(const glm::vec2 & pos) const {}

			std::string getFrame(const std::string & name) const;

		protected:
			Widget * m_widget = nullptr;
		};

		// ...

		class RendererButton : public Renderer
		{
		public:
			RendererButton(Widget & widget) : Renderer(widget) {}

			virtual void onRender(const glm::vec2 & pos) const override final;

			std::string getFrame() const;
		};

		class RendererPanel : public Renderer
		{
		public:
			RendererPanel(Widget & widget) : Renderer(widget) {}

			virtual void onRender(const glm::vec2 & pos) const override final;
		};

		class RendererSlider : public Renderer
		{
		public:
			enum class Component
			{
				BAR_LEFT, BAR_MIDDLE, BAR_RIGHT, MARKER
			};

			RendererSlider(Widget & widget) : Renderer(widget) {}

			virtual void onRender(const glm::vec2 & pos) const override final;

			std::string getFrame(Component component) const;
		};
	}
}