
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

	constexpr const char * VALUE_STATE_CLICKED = "clicked";
	constexpr const char * VALUE_STATE_HOVERED = "hovered";
	constexpr const char * VALUE_STATE_LOCKED = "locked";

	constexpr const char * BUTTON_ICON_ACTIVE = "active";
	constexpr const char * BUTTON_ICON_INACTIVE = "inactive";
	constexpr const char * SLIDER_ICON_BAR_LEFT = "bar_left";
	constexpr const char * SLIDER_ICON_BAR_MIDDLE = "bar_middle";
	constexpr const char * SLIDER_ICON_BAR_RIGHT = "bar_right";
	constexpr const char * SLIDER_ICON_MARKER = "marker";
}

ui::gui::Renderer::Renderer(Widget & widget)
	: m_widget(&widget)
{}

std::string ui::gui::Renderer::getFrame(const std::string & name) const
{
	std::string frame = name;
	const auto & activation = m_widget->m_activation;
	if (activation.m_locked)
		frame = frame + "_" + VALUE_STATE_LOCKED;
	else if (activation.m_button != mouse::Button::NONE)
		frame = frame + "_" + VALUE_STATE_CLICKED;
	else if (activation.m_hovered)
		frame = frame + "_" + VALUE_STATE_HOVERED;
	return frame;
}

// ...

std::string ui::gui::RendererButton::getFrame() const
{
	const auto & activation = m_widget->m_activation;
	if (m_widget->m_state.m_bool)
		return Renderer::getFrame(BUTTON_ICON_ACTIVE);
	else
		return Renderer::getFrame(BUTTON_ICON_INACTIVE);
}

void ui::gui::RendererButton::onRender(const glm::vec2 & pos) const
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

void ui::gui::RendererPanel::onRender(const glm::vec2 & pos) const
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

// ...

void ui::gui::RendererSlider::onRender(const glm::vec2 & pos) const
{
	const auto it = m_widget->m_assets.m_sprites.find(ASSET_SPRITE_ICON);
	if (it == m_widget->m_assets.m_sprites.end() || !it->second)
		return;
	const auto & icon = it->second;

	const auto frameBarLeft = getFrame(Component::BAR_LEFT);
	const auto frameBarMiddle = getFrame(Component::BAR_MIDDLE);
	const auto frameBarRight = getFrame(Component::BAR_RIGHT);
	const auto frameMarker = getFrame(Component::MARKER);

	const glm::vec2 size = m_widget->m_size.m_size;
	const glm::vec2 edgeSize = icon->has(frameBarLeft) ? icon->get(frameBarLeft).getSize() : glm::ivec2{};
	const glm::vec2 centerSize = math::max(glm::vec2{}, size - 2.0f * edgeSize);
	const glm::vec2 centerPos = pos + edgeSize;
	const glm::vec2 edgePos = centerPos + centerSize;
	const glm::vec2 markerSize = icon->has(frameMarker) ? icon->get(frameMarker).getSize() : glm::ivec2{};
	const glm::vec2 markerPos = pos + (size - markerSize.x) * math::max(0.0f, math::min(1.0f, m_widget->m_state.m_float));

	if (icon->has(frameBarLeft))
		icon->get(frameBarLeft).draw({ pos.x, pos.y }, { edgeSize.x, edgeSize.y });
	if (icon->has(frameBarMiddle))
		icon->get(frameBarMiddle).draw({ centerPos.x, pos.y }, { centerSize.x, edgeSize.y });
	if (icon->has(frameBarRight))
		icon->get(frameBarRight).draw({ edgePos.x, pos.y }, { edgeSize.x, edgeSize.y });
	if (icon->has(frameMarker))
		icon->get(frameMarker).draw({ markerPos.x, pos.y }, { markerSize.x, edgeSize.y });
}

std::string ui::gui::RendererSlider::getFrame(Component component) const
{
	switch (component)
	{
	case Component::BAR_LEFT:
		return Renderer::getFrame(SLIDER_ICON_BAR_LEFT);
	case Component::BAR_MIDDLE:
		return Renderer::getFrame(SLIDER_ICON_BAR_MIDDLE);
	case Component::BAR_RIGHT:
		return Renderer::getFrame(SLIDER_ICON_BAR_RIGHT);
	case Component::MARKER:
		return Renderer::getFrame(SLIDER_ICON_MARKER);
	default:
		return "";
	}
}
