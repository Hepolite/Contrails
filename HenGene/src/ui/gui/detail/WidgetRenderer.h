
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
			Renderer(const Widgets & widgets, Widget & widget);
			Renderer(const Renderer &) = default;
			Renderer(Renderer &&) = default;
			virtual ~Renderer() = default;

			Renderer & operator=(const Renderer &) = default;
			Renderer & operator=(Renderer &&) = default;

			virtual void operator()() const {}

		protected:
			const Widgets * m_widgets = nullptr;
			Widget * m_widget = nullptr;
		};

		class RendererButton : public Renderer
		{
		public:
			RendererButton(const Widgets & widgets, Widget & widget);

			virtual void operator()() const override final;
		};
	}
}