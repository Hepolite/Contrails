
#include "WidgetRenderer.h"

ui::gui::Renderer::Renderer(Widget & widget)
	: m_widget(&widget)
{}

// ...

ui::gui::RendererButton::RendererButton(Widget & widget)
	: Renderer(widget)
{}
std::string ui::gui::RendererButton::getFrame() const
{
	std::string frame = m_widget->m_state.m_bool ? "active" : "inactive";
	if (m_widget->m_activation.m_locked)
		frame += "_locked";
	else if (m_widget->m_activation.m_button != mouse::Button::NONE)
		frame += "_clicked";
	return frame;
}

void ui::gui::RendererButton::operator()(const glm::vec2 & pos) const
{
	const auto it = m_widget->m_assets.m_sprites.find("icon");
	if (it == m_widget->m_assets.m_sprites.end())
		return;
	if (const auto icon = it->second)
	{
		const auto frame = getFrame();
		if (icon->has(frame))
			icon->get(frame).draw(pos, m_widget->m_size.m_size);
	}
}