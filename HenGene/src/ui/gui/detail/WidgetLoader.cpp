
#include "WidgetLoader.h"

#include "asset/AssetRegistry.h"
#include "ui/Keyboard.h"
#include "util/Strings.h"

#include <plog/Log.h>

namespace
{
	constexpr const char * NODE_ACTIVATION = "activation";
	constexpr const char * NODE_ASSETS = "assets";
	constexpr const char * NODE_ASSETS_SCRIPTS = "scripts";
	constexpr const char * NODE_ASSETS_SPRITES = "sprites";
	constexpr const char * NODE_BORDER = "border";
	constexpr const char * NODE_FAMILY = "widget";
	constexpr const char * NODE_GROUP = "group";
	constexpr const char * NODE_LINK = "link";
	constexpr const char * NODE_POSITION = "position";
	constexpr const char * NODE_SIZE = "size";
	constexpr const char * NODE_STATE = "state";

	constexpr const char * ATTR_ACTIVATION_KEY = "key";
	constexpr const char * ATTR_BORDER_ALL = "all";
	constexpr const char * ATTR_BORDER_OUTER = "outer";
	constexpr const char * ATTR_BORDER_OUTER_LEFT = "outer_left";
	constexpr const char * ATTR_BORDER_OUTER_RIGHT = "outer_right";
	constexpr const char * ATTR_BORDER_OUTER_TOP = "outer_top";
	constexpr const char * ATTR_BORDER_OUTER_BOTTOM = "outer_bottom";
	constexpr const char * ATTR_BORDER_INNER = "inner";
	constexpr const char * ATTR_BORDER_INNER_LEFT = "inner_left";
	constexpr const char * ATTR_BORDER_INNER_RIGHT = "inner_right";
	constexpr const char * ATTR_BORDER_INNER_TOP = "inner_top";
	constexpr const char * ATTR_BORDER_INNER_BOTTOM = "inner_bottom";
	constexpr const char * ATTR_FAMILY_NAME = "name";
	constexpr const char * ATTR_FAMILY_TYPE = "type";
	constexpr const char * ATTR_GROUP_LEADER = "leader";
	constexpr const char * ATTR_LINK_TARGET = "target";
	constexpr const char * ATTR_LINK_LOCATION = "location";
	constexpr const char * ATTR_SIZE_MIN = "min";
	constexpr const char * ATTR_SIZE_MAX = "max";
	constexpr const char * ATTR_STATE_LOCKED = "locked";
	constexpr const char * ATTR_STATE_VALUE = "value";

	constexpr const char * VALUE_LINK_PARENT = "parent";
	constexpr const char * VALUE_LINK_TOP_LEFT = "top_left";
	constexpr const char * VALUE_LINK_TOP = "top";
	constexpr const char * VALUE_LINK_TOP_RIGHT = "top_right";
	constexpr const char * VALUE_LINK_LEFT_TOP = "left_top";
	constexpr const char * VALUE_LINK_RIGHT_TOP = "right_top";
	constexpr const char * VALUE_LINK_LEFT = "left";
	constexpr const char * VALUE_LINK_CENTER = "center";
	constexpr const char * VALUE_LINK_RIGHT = "right";
	constexpr const char * VALUE_LINK_LEFT_BOTTOM = "left_bottom";
	constexpr const char * VALUE_LINK_RIGHT_BOTTOM = "right_bottom";
	constexpr const char * VALUE_LINK_BOTTOM_LEFT = "bottom_left";
	constexpr const char * VALUE_LINK_BOTTOM = "bottom";
	constexpr const char * VALUE_LINK_BOTTOM_RIGHT = "bottom_right";
}

ui::gui::WidgetLoader::WidgetLoader(Widgets & widgets, Widget & widget)
	: m_widgets(&widgets), m_widget(&widget)
{}

void ui::gui::WidgetLoader::load(const pugi::xml_node & node)
{
	loadFamily(node);
	loadGroup(node.child(NODE_GROUP));
	loadLink(node.child(NODE_LINK));

	if (const auto child = node.child(NODE_ACTIVATION))
		loadActivation(child);
	if (const auto child = node.child(NODE_ASSETS))
		loadAssets(child);
	if (const auto child = node.child(NODE_BORDER))
		loadBorder(child);
	if (const auto child = node.child(NODE_POSITION))
		loadPosition(child);
	if (const auto child = node.child(NODE_SIZE))
		loadSize(child);
	if (const auto child = node.child(NODE_STATE))
		loadState(child);
}

void ui::gui::WidgetLoader::loadActivation(const pugi::xml_node & node)
{
	const std::string attrKey = node.attribute(ATTR_ACTIVATION_KEY).as_string();

	const auto parts = string::split(attrKey, '+');
	if (parts.size() > 1u)
	{
		for (unsigned int i = 0u; i < parts.size(); ++i)
			m_widget->m_activation.m_mask |= keyboard::nameToModifier(parts[i]);
	}
	if (!parts.empty())
		m_widget->m_activation.m_key = keyboard::nameToKey(parts.back());
}
void ui::gui::WidgetLoader::loadAssets(const pugi::xml_node & node)
{
	if (const auto scripts = node.child(NODE_ASSETS_SCRIPTS))
	{
		for (auto attr = scripts.first_attribute(); attr; attr = attr.next_attribute())
			m_widget->m_assets.m_scripts[attr.name()] = attr.as_string();
	}
	if (const auto sprites = node.child(NODE_ASSETS_SPRITES))
	{
		if (m_assets != nullptr)
		{
			for (auto attr = sprites.first_attribute(); attr; attr = attr.next_attribute())
				m_widget->m_assets.m_sprites[attr.name()] = m_assets->get<render::allegro::Sprite>(attr.as_string());
		}
	}
}
void ui::gui::WidgetLoader::loadBorder(const pugi::xml_node & node)
{
	const auto attrAll = node.attribute(ATTR_BORDER_ALL).as_float();
	const auto attrOuter = node.attribute(ATTR_BORDER_OUTER).as_float(attrAll);
	const auto attrInner = node.attribute(ATTR_BORDER_INNER).as_float(attrAll);

	m_widget->m_border.m_inner.x = node.attribute(ATTR_BORDER_INNER_LEFT).as_float(attrInner);
	m_widget->m_border.m_inner.y = node.attribute(ATTR_BORDER_INNER_RIGHT).as_float(attrInner);
	m_widget->m_border.m_inner.z = node.attribute(ATTR_BORDER_INNER_TOP).as_float(attrInner);
	m_widget->m_border.m_inner.w = node.attribute(ATTR_BORDER_INNER_BOTTOM).as_float(attrInner);
	m_widget->m_border.m_outer.x = node.attribute(ATTR_BORDER_OUTER_LEFT).as_float(attrOuter);
	m_widget->m_border.m_outer.y = node.attribute(ATTR_BORDER_OUTER_RIGHT).as_float(attrOuter);
	m_widget->m_border.m_outer.z = node.attribute(ATTR_BORDER_OUTER_TOP).as_float(attrOuter);
	m_widget->m_border.m_outer.w = node.attribute(ATTR_BORDER_OUTER_BOTTOM).as_float(attrOuter);
}
void ui::gui::WidgetLoader::loadFamily(const pugi::xml_node & node)
{
	for (auto child = node.first_child(); child; child = child.next_sibling())
	{
		if (std::strcmp(child.name(), NODE_FAMILY) != 0)
			continue;
		const std::string attrName = child.attribute(ATTR_FAMILY_NAME).as_string();
		const std::string attrType = child.attribute(ATTR_FAMILY_TYPE).as_string();

		auto & widget = m_widgets->create(attrName, m_widget->m_name);
		WidgetLoader loader{ *m_widgets, widget };
		loader.inject(*m_assets);
		loader.load(child);
	}
}
void ui::gui::WidgetLoader::loadGroup(const pugi::xml_node & node)
{
	if (const auto attr = node.attribute(ATTR_GROUP_LEADER))
	{
		auto & leader = m_widgets->get(attr.as_string());
		m_widget->m_group.m_leader = leader.m_name;
		leader.m_group.m_members.insert(m_widget->m_name);
	}
	else
		m_widget->m_group.m_members.insert(m_widget->m_name);
}
void ui::gui::WidgetLoader::loadLink(const pugi::xml_node & node)
{
	const std::string attrTarget = node.attribute(ATTR_LINK_TARGET).as_string(VALUE_LINK_PARENT);
	const std::string attrLocation = node.attribute(ATTR_LINK_LOCATION).as_string(VALUE_LINK_TOP_LEFT);

	if (attrTarget == VALUE_LINK_PARENT)
		m_widget->m_link.m_target = m_widget->m_family.m_parent;
	else
		m_widget->m_link.m_target = attrTarget;

	if (attrLocation == VALUE_LINK_TOP_LEFT)
		m_widget->m_link.m_location = Link::Location::TOP_LEFT;
	else if (attrLocation == VALUE_LINK_TOP)
		m_widget->m_link.m_location = Link::Location::TOP;
	else if (attrLocation == VALUE_LINK_TOP_RIGHT)
		m_widget->m_link.m_location = Link::Location::TOP_RIGHT;
	else if (attrLocation == VALUE_LINK_LEFT_TOP)
		m_widget->m_link.m_location = Link::Location::LEFT_TOP;
	else if (attrLocation == VALUE_LINK_RIGHT_TOP)
		m_widget->m_link.m_location = Link::Location::RIGHT_TOP;
	else if (attrLocation == VALUE_LINK_LEFT)
		m_widget->m_link.m_location = Link::Location::LEFT;
	else if (attrLocation == VALUE_LINK_CENTER)
		m_widget->m_link.m_location = Link::Location::CENTER;
	else if (attrLocation == VALUE_LINK_RIGHT)
		m_widget->m_link.m_location = Link::Location::RIGHT;
	else if (attrLocation == VALUE_LINK_LEFT_BOTTOM)
		m_widget->m_link.m_location = Link::Location::LEFT_BOTTOM;
	else if (attrLocation == VALUE_LINK_RIGHT_BOTTOM)
		m_widget->m_link.m_location = Link::Location::RIGHT_BOTTOM;
	else if (attrLocation == VALUE_LINK_BOTTOM_LEFT)
		m_widget->m_link.m_location = Link::Location::BOTTOM_LEFT;
	else if (attrLocation == VALUE_LINK_BOTTOM)
		m_widget->m_link.m_location = Link::Location::BOTTOM;
	else if (attrLocation == VALUE_LINK_BOTTOM_RIGHT)
		m_widget->m_link.m_location = Link::Location::BOTTOM_RIGHT;
	else
		LOG_WARNING << "Unknown location tag " << attrLocation;
}
void ui::gui::WidgetLoader::loadPosition(const pugi::xml_node & node)
{
	if (const auto child = node.first_child())
	{
		m_widget->m_position.m_pos = string::parse<glm::vec2>(child.value());
		m_widget->m_position.m_automatic = false;
	}
}
void ui::gui::WidgetLoader::loadSize(const pugi::xml_node & node)
{
	if (const auto attr = node.attribute(ATTR_SIZE_MIN))
		m_widget->m_size.m_minSize = string::parse<glm::vec2>(attr.as_string());
	if (const auto attr = node.attribute(ATTR_SIZE_MAX))
		m_widget->m_size.m_maxSize = string::parse<glm::vec2>(attr.as_string());
	if (const auto child = node.first_child())
	{
		m_widget->m_size.m_size = string::parse<glm::vec2>(child.value());
		m_widget->m_size.m_automatic = false;
	}
}
void ui::gui::WidgetLoader::loadState(const pugi::xml_node & node)
{
	if (const auto attr = node.attribute(ATTR_STATE_LOCKED))
		m_widget->m_state.m_locked = attr.as_bool();
	if (const auto attr = node.attribute(ATTR_STATE_VALUE))
		m_widget->m_state.m_value = attr.as_string();
}
