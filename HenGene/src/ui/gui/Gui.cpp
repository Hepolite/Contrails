
#include "Gui.h"

#include <vector>

namespace
{
	constexpr const char * ROOT = "";
	constexpr const char * ASSET_SCRIPT_ACTIVATE = "activate";

	std::vector<ui::gui::Widget*> getChildren(ui::gui::Widgets & widgets, ui::gui::Widget & widget)
	{
		std::vector<ui::gui::Widget*> children;
		for (const auto & name : widget.m_family.m_children)
			children.push_back(&widgets.get(name));
		return children;
	}
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

void ui::gui::Gui::onEvent(const logic::event::DisplayResize & event)
{
	m_widgets.get().m_size.m_size = event.m_size;
}
bool ui::gui::Gui::onEvent(const logic::event::KeyPress & event)
{
	return false;
}
void ui::gui::Gui::onEvent(const logic::event::KeyRelease & event)
{
}
bool ui::gui::Gui::onEvent(const logic::event::MousePress & event)
{
	return onEvent(event, m_widgets.get());
}
bool ui::gui::Gui::onEvent(const logic::event::MousePress & event, Widget & widget)
{
	// If any child widget is clicked, the current widget is NOT clicked
	for (const auto & name : widget.m_family.m_children)
	{
		if (onEvent(event, m_widgets.get(name)))
			return true;
	}

	if (!widget.m_activation.m_hovered || widget.m_activation.m_locked || !widget.m_render.m_visible)
		return false;
	widget.m_activation.m_button = event.m_button;
	return true;
}
bool ui::gui::Gui::onEvent(const logic::event::MouseMove & event)
{
	// Before deciding which widget is being hovered, force any currently hovered widgets to be reset
	for (auto & it : m_widgets)
		it.second.m_activation.m_hovered = false;
	return onEvent(event, m_widgets.get(), { 0.0f, 0.0f });
}
bool ui::gui::Gui::onEvent(const logic::event::MouseMove & event, Widget & widget, const glm::vec2 & offset)
{
	// If any child widget is hovered, the current widget is NOT hovered
	for (const auto & name : widget.m_family.m_children)
	{
		if (onEvent(event, m_widgets.get(name), widget.m_position.m_pos + offset))
			return true;
	}

	const auto bbox = (event.m_pos - (widget.m_position.m_pos + offset)) / widget.m_size.m_size;
	widget.m_activation.m_hovered = !widget.m_activation.m_locked && widget.m_render.m_visible &&
		bbox.x >= 0.0f && bbox.x <= 1.0f && bbox.y >= 0.0f && bbox.y <= 1.0f;
	return widget.m_activation.m_hovered;
}
void ui::gui::Gui::onEvent(const logic::event::MouseRelease & event)
{
	onEvent(event, m_widgets.get());
	for (auto & it : m_widgets)
		it.second.m_activation.m_button = mouse::Button::NONE;
}
void ui::gui::Gui::onEvent(const logic::event::MouseRelease & event, Widget & widget)
{
	// Ensure that the event is passed down to all children
	for (const auto & name : widget.m_family.m_children)
		onEvent(event, m_widgets.get(name));

	if (widget.m_activation.m_hovered && !widget.m_activation.m_locked && widget.m_render.m_visible &&
		widget.m_activation.m_button != mouse::Button::NONE)
		m_script.execute(widget.m_assets.m_scripts[ASSET_SCRIPT_ACTIVATE]);
}