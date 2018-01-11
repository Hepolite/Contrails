
#include "WidgetRenderer.h"

#include "util/MathGeneric.h"

namespace
{
	constexpr const char * ASSET_SPRITE_BACKGROUND = "background";
	constexpr const char * ASSET_SPRITE_ICON = "icon";

	constexpr const char * VALUE_BACKGROUND_TOP_LEFT = "top_left";
	constexpr const char * VALUE_BACKGROUND_TOP = "top";
	constexpr const char * VALUE_BACKGROUND_TOP_RIGHT = "top_right";
	constexpr const char * VALUE_BACKGROUND_LEFT = "left";
	constexpr const char * VALUE_BACKGROUND_CENTER = "center";
	constexpr const char * VALUE_BACKGROUND_RIGHT = "right";
	constexpr const char * VALUE_BACKGROUND_BOTTOM_LEFT = "bottom_left";
	constexpr const char * VALUE_BACKGROUND_BOTTOM = "bottom";
	constexpr const char * VALUE_BACKGROUND_BOTTOM_RIGHT = "bottom_right";
	constexpr const char * VALUE_ICON_ACTIVE = "active";
	constexpr const char * VALUE_ICON_ACTIVE_CLICKED = "active_clicked";
	constexpr const char * VALUE_ICON_ACTIVE_HOVERED = "active_hovered";
	constexpr const char * VALUE_ICON_ACTIVE_LOCKED = "active_locked";
	constexpr const char * VALUE_ICON_INACTIVE = "inactive";
	constexpr const char * VALUE_ICON_INACTIVE_CLICKED = "inactive_clicked";
	constexpr const char * VALUE_ICON_INACTIVE_HOVERED = "inactive_hovered";
	constexpr const char * VALUE_ICON_INACTIVE_LOCKED = "inactive_locked";
}

ui::gui::Renderer::Renderer(Widget & widget)
	: m_widget(&widget)
{}

// ...

ui::gui::RendererButton::RendererButton(Widget & widget)
	: Renderer(widget)
{}
std::string ui::gui::RendererButton::getFrame() const
{
	const auto & activation = m_widget->m_activation;
	if (m_widget->m_state.m_bool)
	{
		if (activation.m_locked)
			return VALUE_ICON_ACTIVE_LOCKED;
		else if (activation.m_button != mouse::Button::NONE)
			return VALUE_ICON_ACTIVE_CLICKED;
		else if (activation.m_hovered)
			return VALUE_ICON_ACTIVE_HOVERED;
		else
			return VALUE_ICON_ACTIVE;
	}
	else
	{
		if (activation.m_locked)
			return VALUE_ICON_INACTIVE_LOCKED;
		else if (activation.m_button != mouse::Button::NONE)
			return VALUE_ICON_INACTIVE_CLICKED;
		else if (activation.m_hovered)
			return VALUE_ICON_INACTIVE_HOVERED;
		else
			return VALUE_ICON_INACTIVE;
	}
}

void ui::gui::RendererButton::operator()(const glm::vec2 & pos) const
{
	const auto it = m_widget->m_assets.m_sprites.find(ASSET_SPRITE_ICON);
	if (it == m_widget->m_assets.m_sprites.end() || !it->second)
		return;
	const auto & icon = it->second;
	
	const auto frame = getFrame();
	if (icon->has(frame))
		icon->get(frame).draw(pos, m_widget->m_size.m_size);
}

// ...

ui::gui::RendererPanel::RendererPanel(Widget & widget)
	: Renderer(widget)
{}

void ui::gui::RendererPanel::operator()(const glm::vec2 & pos) const
{
	const auto it = m_widget->m_assets.m_sprites.find(ASSET_SPRITE_BACKGROUND);
	if (it == m_widget->m_assets.m_sprites.end() || !it->second)
		return;
	const auto & background = it->second;

	const glm::vec2 size = m_widget->m_size.m_size;
	const glm::vec2 cornerSize = background->has(VALUE_BACKGROUND_TOP_LEFT) ? background->get(VALUE_BACKGROUND_TOP_LEFT).getSize() : glm::ivec2{};
	const glm::vec2 centerSize = math::max(glm::vec2{}, size - 2.0f * cornerSize);
	const glm::vec2 centerPos = pos + cornerSize;
	const glm::vec2 cornerPos = centerPos + centerSize;

	if (background->has(VALUE_BACKGROUND_TOP_LEFT))
		background->get(VALUE_BACKGROUND_TOP_LEFT).draw({ pos.x, pos.y }, { cornerSize.x, cornerSize.y });
	if (background->has(VALUE_BACKGROUND_TOP))
		background->get(VALUE_BACKGROUND_TOP).draw({ centerPos.x, pos.y }, { centerSize.x, cornerSize.y });
	if (background->has(VALUE_BACKGROUND_TOP_RIGHT))
		background->get(VALUE_BACKGROUND_TOP_RIGHT).draw({ cornerPos.x, pos.y }, { cornerSize.x, cornerSize.y });
	if (background->has(VALUE_BACKGROUND_LEFT))
		background->get(VALUE_BACKGROUND_LEFT).draw({ pos.x, centerPos.y }, { cornerSize.x, centerSize.y });
	if (background->has(VALUE_BACKGROUND_CENTER))
		background->get(VALUE_BACKGROUND_CENTER).draw({ centerPos.x, centerPos.y }, { centerSize.x, centerSize.y });
	if (background->has(VALUE_BACKGROUND_RIGHT))
		background->get(VALUE_BACKGROUND_RIGHT).draw({ cornerPos.x, centerPos.y }, { cornerSize.x, centerSize.y });
	if (background->has(VALUE_BACKGROUND_BOTTOM_LEFT))
		background->get(VALUE_BACKGROUND_BOTTOM_LEFT).draw({ pos.x, cornerPos.y }, { cornerSize.x, cornerSize.y });
	if (background->has(VALUE_BACKGROUND_BOTTOM))
		background->get(VALUE_BACKGROUND_BOTTOM).draw({ centerPos.x, cornerPos.y }, { centerSize.x, cornerSize.y });
	if (background->has(VALUE_BACKGROUND_BOTTOM_RIGHT))
		background->get(VALUE_BACKGROUND_BOTTOM_RIGHT).draw({ cornerPos.x, cornerPos.y }, { cornerSize.x, cornerSize.y });
}