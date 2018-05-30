
#include "Gui.h"

#include <vector>


#include "render/allegro/Text.h"
#include "asset/AssetRegistry.h"
#include "asset/factory/FactoryFont.h"

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



	asset::AssetRegistry m_registry;
	m_registry.add<render::allegro::Font>("font").m_factory = []()
	{
		auto asset = std::make_unique<render::allegro::Font>();
		asset::factory::LoaderFont{}.load(*asset, "data/fonts/debug.ttf");
		return asset;
	};

	render::allegro::Text text;
	auto & component = text.add<render::allegro::ComponentString>();
	component.setString({ "Hello World! This is a rather long string which should be split into multiple parts. I can even\nmanually\nsplit\nit\nat\nwill." });
	component.setFont(m_registry.get<render::allegro::Font>("font"));
	component.setSize(18u);

	text.draw({ 0, 0 }, { 150, 200 }, 0.0_s);
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
	// If the widget is invisible or not hovered, it cannot be clicked; consider it clicked otherwise
	if (!widget.m_activation.m_hovered || !widget.m_render.m_visible)
		return false;
	if (!widget.m_activation.m_locked && widget.m_activation.m_button == mouse::Button::NONE)
		widget.m_activation.m_button = event.m_button;
	return true;
}
bool ui::gui::Gui::onEvent(const logic::event::MouseMove & event)
{
	// Before deciding which widget is being hovered, force any currently hovered widgets to be reset
	for (auto & it : m_widgets)
	{
		it.second.m_activation.m_hovered = false;
		it.second.m_activation.m_mousePosition = event.m_pos;
	}
	return onEvent(event, m_widgets.get(), { 0.0f, 0.0f });
}
bool ui::gui::Gui::onEvent(const logic::event::MouseMove & event, Widget & widget, const glm::vec2 & offset)
{
	// If the widget is invisible, it cannot be hovered, nor can any of its children
	if (!widget.m_render.m_visible)
		return false;

	// If any child widget is hovered, the current widget is NOT hovered
	for (const auto & name : widget.m_family.m_children)
	{
		if (onEvent(event, m_widgets.get(name), widget.m_position.m_pos + offset))
			return true;
	}
	const auto bbox = (event.m_pos - (widget.m_position.m_pos + offset)) / widget.m_size.m_size;
	widget.m_activation.m_hovered = bbox.x >= 0.0f && bbox.x <= 1.0f && bbox.y >= 0.0f && bbox.y <= 1.0f;
	return widget.m_activation.m_hovered;
}
void ui::gui::Gui::onEvent(const logic::event::MouseRelease & event)
{
	onEvent(event, m_widgets.get());
	for (auto & it : m_widgets)
	{
		if (it.second.m_activation.m_button == event.m_button)
			it.second.m_activation.m_button = mouse::Button::NONE;
	}
}
void ui::gui::Gui::onEvent(const logic::event::MouseRelease & event, Widget & widget)
{
	// Ensure that the event is passed down to all children
	for (const auto & name : widget.m_family.m_children)
		onEvent(event, m_widgets.get(name));

	if (!widget.m_activation.m_locked && widget.m_render.m_visible && widget.m_activation.m_button == event.m_button)
		widget.m_logic.m_action(m_script);
}