
#include "Gui.h"

namespace
{
	constexpr const char * ROOT = "";
}

void ui::gui::Gui::process()
{
	process(m_widgets.get(ROOT), { 0.0f, 0.0f });
}
void ui::gui::Gui::process(Widget & widget, const glm::vec2 & offset)
{
	for (const auto name : widget.m_family.m_children)
		process(m_widgets.get(name), widget.m_position.m_pos);
	widget.m_logic.m_process(widget.m_position.m_pos + offset);
}

void ui::gui::Gui::render() const
{
	render(m_widgets.get(ROOT), { 0.0f, 0.0f });
}
void ui::gui::Gui::render(const Widget & widget, const glm::vec2 & offset) const
{
	if (widget.m_render.m_visible)
	{
		widget.m_render.m_render(widget.m_position.m_pos + widget.m_render.m_offset + offset);
		for (const auto name : widget.m_family.m_children)
			render(m_widgets.get(name), widget.m_position.m_pos + widget.m_render.m_offset + offset);
	}
}
