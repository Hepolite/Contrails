
#include "WidgetProcessor.h"

#include "util/MathGeneric.h"

namespace
{
	constexpr const char * ASSET_SCRIPT_ACTION = "action";
}

ui::gui::Processor::Processor(Widgets & widgets, Widget & widget)
	: m_widgets(&widgets), m_widget(&widget)
{}

void ui::gui::Processor::onProcess(const glm::vec2 & pos)
{
	if (m_widget->m_size.m_automatic)
		m_widget->m_size.m_size = calculateSize();
	if (m_widget->m_position.m_automatic)
		m_widget->m_position.m_pos = calculatePosition();
}
void ui::gui::Processor::onAction(const logic::script::Script & script)
{
	script.execute(m_widget->m_assets.m_scripts[ASSET_SCRIPT_ACTION]);
}

const ui::gui::Widget & ui::gui::Processor::getParent() const
{
	return m_widgets->get(m_widget->m_family.m_parent);
}
const ui::gui::Widget & ui::gui::Processor::getChild(const std::string & name) const
{
	if (m_widget->m_family.m_children.find(name) == m_widget->m_family.m_children.end())
		throw std::invalid_argument(name + " is not a child of " + m_widget->m_header.m_name);
	return m_widgets->get(name);
}

glm::vec2 ui::gui::Processor::calculatePosition() const
{
	if (!m_widgets->has(m_widget->m_link.m_target))
		return {};
	const auto & target = m_widgets->get(m_widget->m_link.m_target);
	const auto targetPos = target.m_position.m_pos;
	const auto targetSize = target.m_size.m_size;
	const auto size = m_widget->m_size.m_size;
	const auto deltaSize = targetSize - size;

	if (m_widget->m_link.m_target == m_widget->m_family.m_parent)
	{
		const auto border = math::max(m_widget->m_border.m_outer, target.m_border.m_inner);
		switch (m_widget->m_link.m_location)
		{
		case Link::Location::TOP_LEFT:
		case Link::Location::LEFT_TOP:
			return glm::vec2{ border.x, border.z };
		case Link::Location::TOP:
			return glm::vec2{ 0.5f * deltaSize.x, border.z };
		case Link::Location::TOP_RIGHT:
		case Link::Location::RIGHT_TOP:
			return glm::vec2{ deltaSize.x - border.y, border.z };
		case Link::Location::LEFT:
			return glm::vec2{ border.x, 0.5f * deltaSize.y };
		case Link::Location::CENTER:
			return 0.5f * deltaSize;
		case Link::Location::RIGHT:
			return glm::vec2{ deltaSize.x - border.y, 0.5f * deltaSize.y };
		case Link::Location::BOTTOM_LEFT:
		case Link::Location::LEFT_BOTTOM:
			return glm::vec2{ border.x, deltaSize.y - border.w };
		case Link::Location::BOTTOM:
			return glm::vec2{ 0.5f * deltaSize.x, deltaSize.y - border.w };
		case Link::Location::BOTTOM_RIGHT:
		case Link::Location::RIGHT_BOTTOM:
			return glm::vec2{ deltaSize.x - border.y, deltaSize.y - border.w };
		}
	}
	else
	{
		const auto thisBorder = m_widget->m_border.m_outer;
		const auto targetBorder = target.m_border.m_outer;
		const auto border = glm::vec4{
			math::max(targetBorder.x, thisBorder.y), math::max(targetBorder.y, thisBorder.x),
			math::max(targetBorder.z, thisBorder.w), math::max(targetBorder.w, thisBorder.z),
		};
		switch (m_widget->m_link.m_location)
		{
		case Link::Location::TOP_LEFT:
			return glm::vec2{ targetPos.x, targetPos.y - size.y - border.z };
		case Link::Location::TOP:
			return glm::vec2{ targetPos.x + 0.5f * deltaSize.x, targetPos.y - size.y - border.z };
		case Link::Location::TOP_RIGHT:
			return glm::vec2{ targetPos.x + deltaSize.x, targetPos.y - size.y - border.z };
		case Link::Location::LEFT_TOP:
			return glm::vec2{ targetPos.x - size.x - border.x, targetPos.y };
		case Link::Location::RIGHT_TOP:
			return glm::vec2{ targetPos.x + targetSize.x + border.y, targetPos.y };
		case Link::Location::LEFT:
			return glm::vec2{ targetPos.x - size.x - border.x, targetPos.y + 0.5f * deltaSize.y };
		case Link::Location::CENTER:
			return targetPos + 0.5f * deltaSize;
		case Link::Location::RIGHT:
			return glm::vec2{ targetPos.x + targetSize.x + border.y, targetPos.y + 0.5f * deltaSize.y };
		case Link::Location::LEFT_BOTTOM:
			return glm::vec2{ targetPos.x - size.x - border.x, targetPos.y + deltaSize.y };
		case Link::Location::RIGHT_BOTTOM:
			return glm::vec2{ targetPos.x + targetSize.x + border.y, targetPos.y + deltaSize.y };
		case Link::Location::BOTTOM_LEFT:
			return glm::vec2{ targetPos.x, targetPos.y + targetSize.y + border.w };
		case Link::Location::BOTTOM:
			return glm::vec2{ targetPos.x + 0.5f * deltaSize.x, targetPos.y + targetSize.y + border.w };
		case Link::Location::BOTTOM_RIGHT:
			return glm::vec2{ targetPos.x + deltaSize.x, targetPos.y + targetSize.y + border.w };
		}
	}
	return glm::vec2{};
}
glm::vec2 ui::gui::Processor::calculateSize() const
{
	glm::vec2 minSize = m_widget->m_size.m_minSize;
	for (const auto & name : m_widget->m_family.m_children)
	{
		auto & child = getChild(name);
		if (!child.m_render.m_visible)
			continue;
		if (child.m_link.m_target == m_widget->m_header.m_name &&
			child.m_link.m_location != Link::Location::TOP_LEFT &&
			child.m_link.m_location != Link::Location::LEFT_TOP &&
			child.m_position.m_automatic
		) continue;
		const auto border = glm::vec2{
			math::max(m_widget->m_border.m_inner.y, child.m_border.m_outer.y),
			math::max(m_widget->m_border.m_inner.w, child.m_border.m_outer.w) 
		};
		minSize = math::max(minSize, child.m_position.m_pos + child.m_size.m_size + border);
	}
	return math::min(minSize, m_widget->m_size.m_maxSize);
}

// ...

void ui::gui::ProcessorButtonCheckbox::onAction(const logic::script::Script & script)
{
	m_widget->m_state.m_bool = !m_widget->m_state.m_bool;
	Processor::onAction(script);
}
void ui::gui::ProcessorButtonRadio::onAction(const logic::script::Script & script)
{
	if (m_widget->m_state.m_bool)
		return;

	auto & leader = m_widgets->get(m_widget->m_group.m_leader);
	for (const auto name : leader.m_group.m_members)
	{
		auto & member = m_widgets->get(name);
		if (member.m_state.m_bool)
		{
			member.m_state.m_bool = false;
			Processor{ *m_widgets, member }.onAction(script);
		}
	}

	m_widget->m_state.m_bool = true;
	Processor::onAction(script);
}
