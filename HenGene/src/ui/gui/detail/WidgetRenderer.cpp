
#include "WidgetRenderer.h"

ui::gui::Renderer::Renderer(const Widgets & widgets, Widget & widget)
	: m_widgets(&widgets), m_widget(&widget)
{}

ui::gui::RendererButton::RendererButton(const Widgets & widgets, Widget & widget)
	: Renderer(widgets, widget)
{}
void ui::gui::RendererButton::operator()() const
{
}
