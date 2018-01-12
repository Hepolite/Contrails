
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

			virtual void operator()(const glm::vec2 & pos) const {}

		protected:
			Widget * m_widget = nullptr;
		};

		class RendererButton : public Renderer
		{
		public:
			RendererButton(Widget & widget) : Renderer(widget) {}

			virtual void operator()(const glm::vec2 & pos) const override final;

			std::string getFrame() const;
		};

		class RendererPanel : public Renderer
		{
		public:
			RendererPanel(Widget & widget) : Renderer(widget) {}

			virtual void operator()(const glm::vec2 & pos) const override final;
		};
	}
}