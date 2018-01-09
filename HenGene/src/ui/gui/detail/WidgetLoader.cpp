
#include "WidgetLoader.h"

#include "util/StringParsing.h"

#include <plog/Log.h>

namespace
{
	constexpr const char * NODE_ACTIVATION = "activation";
	constexpr const char * NODE_ASSETS = "assets";
	constexpr const char * NODE_BORDER = "border";
	constexpr const char * NODE_FAMILY = "family";
	constexpr const char * NODE_GROUP = "group";
	constexpr const char * NODE_LINK = "link";
	constexpr const char * NODE_POSITION = "position";
	constexpr const char * NODE_SIZE = "size";
	constexpr const char * NODE_STATE = "state";

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

void ui::gui::WidgetLoader::load(Widget & widget, const pugi::xml_node & node)
{
	loadFamily(widget, node);

	if (const auto child = node.child(NODE_ACTIVATION))
		loadActivation(widget, child);
	if (const auto child = node.child(NODE_ASSETS))
		loadAssets(widget, child);
	if (const auto child = node.child(NODE_BORDER))
		loadBorder(widget, child);
	if (const auto child = node.child(NODE_GROUP))
		loadGroup(widget, child);
	if (const auto child = node.child(NODE_LINK))
		loadLink(widget, child);
	if (const auto child = node.child(NODE_POSITION))
		loadPosition(widget, child);
	if (const auto child = node.child(NODE_SIZE))
		loadSize(widget, child);
	if (const auto child = node.child(NODE_STATE))
		loadState(widget, child);
}

void ui::gui::WidgetLoader::loadActivation(Widget & widget, const pugi::xml_node & node)
{
}
void ui::gui::WidgetLoader::loadAssets(Widget & widget, const pugi::xml_node & node)
{
}
void ui::gui::WidgetLoader::loadBorder(Widget & widget, const pugi::xml_node & node)
{
}
void ui::gui::WidgetLoader::loadFamily(Widget & widget, const pugi::xml_node & node)
{
}
void ui::gui::WidgetLoader::loadGroup(Widget & widget, const pugi::xml_node & node)
{
}
void ui::gui::WidgetLoader::loadLink(Widget & widget, const pugi::xml_node & node)
{
	const std::string attrTarget = node.attribute(ATTR_LINK_TARGET).as_string(VALUE_LINK_PARENT);
	const std::string attrLocation = node.attribute(ATTR_LINK_LOCATION).as_string(VALUE_LINK_TOP_LEFT);

	if (attrTarget == VALUE_LINK_PARENT)
		widget.m_link.m_target = widget.m_family.m_parent;
	else
		widget.m_link.m_target = attrTarget;

	if (attrLocation == VALUE_LINK_TOP_LEFT)
		widget.m_link.m_location = Link::Location::TOP_LEFT;
	else if (attrLocation == VALUE_LINK_TOP)
		widget.m_link.m_location = Link::Location::TOP;
	else if (attrLocation == VALUE_LINK_TOP_RIGHT)
		widget.m_link.m_location = Link::Location::TOP_RIGHT;
	else if (attrLocation == VALUE_LINK_LEFT_TOP)
		widget.m_link.m_location = Link::Location::LEFT_TOP;
	else if (attrLocation == VALUE_LINK_RIGHT_TOP)
		widget.m_link.m_location = Link::Location::RIGHT_TOP;
	else if (attrLocation == VALUE_LINK_LEFT)
		widget.m_link.m_location = Link::Location::LEFT;
	else if (attrLocation == VALUE_LINK_CENTER)
		widget.m_link.m_location = Link::Location::CENTER;
	else if (attrLocation == VALUE_LINK_RIGHT)
		widget.m_link.m_location = Link::Location::RIGHT;
	else if (attrLocation == VALUE_LINK_LEFT_BOTTOM)
		widget.m_link.m_location = Link::Location::LEFT_BOTTOM;
	else if (attrLocation == VALUE_LINK_RIGHT_BOTTOM)
		widget.m_link.m_location = Link::Location::RIGHT_BOTTOM;
	else if (attrLocation == VALUE_LINK_BOTTOM_LEFT)
		widget.m_link.m_location = Link::Location::BOTTOM_LEFT;
	else if (attrLocation == VALUE_LINK_BOTTOM)
		widget.m_link.m_location = Link::Location::BOTTOM;
	else if (attrLocation == VALUE_LINK_BOTTOM_RIGHT)
		widget.m_link.m_location = Link::Location::BOTTOM_RIGHT;
	else
		LOG_WARNING << "Unknown location tag " << attrLocation;
}
void ui::gui::WidgetLoader::loadPosition(Widget & widget, const pugi::xml_node & node)
{
	if (const auto child = node.first_child())
	{
		widget.m_position.m_pos = string::parse<glm::vec2>(child.value());
		widget.m_position.m_automatic = false;
	}
}
void ui::gui::WidgetLoader::loadSize(Widget & widget, const pugi::xml_node & node)
{
	if (const auto attr = node.attribute(ATTR_SIZE_MIN))
		widget.m_size.m_minSize = string::parse<glm::vec2>(attr.as_string());
	if (const auto attr = node.attribute(ATTR_SIZE_MAX))
		widget.m_size.m_maxSize = string::parse<glm::vec2>(attr.as_string());
	if (const auto child = node.first_child())
	{
		widget.m_size.m_size = string::parse<glm::vec2>(child.value());
		widget.m_size.m_automatic = false;
	}
}
void ui::gui::WidgetLoader::loadState(Widget & widget, const pugi::xml_node & node)
{
	if (const auto attr = node.attribute(ATTR_STATE_LOCKED))
		widget.m_state.m_locked = attr.as_bool();
	if (const auto attr = node.attribute(ATTR_STATE_VALUE))
		widget.m_state.m_value = attr.as_string();
}
