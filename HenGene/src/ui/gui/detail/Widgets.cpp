
#include "Widgets.h"


ui::gui::Widget & ui::gui::Widgets::create(const std::string & name, const std::string & parent)
{
	if (has(name) || !has(parent))
		throw std::invalid_argument("Either widget " + name + " already exists, or parent " + parent + " does not exist");

	auto & widget = m_widgets.emplace(name, Widget{}).first->second;
	widget.m_header.m_name = name;
	widget.m_family.m_parent = parent;
	get(parent).m_family.m_children.insert(name);
	return widget;
}

ui::gui::Widget & ui::gui::Widgets::get(const std::string & name)
{
	const auto it = m_widgets.find(name);
	if (it == m_widgets.end())
		throw std::invalid_argument("Widget " + name + " does not exist");
	return it->second;
}
const ui::gui::Widget & ui::gui::Widgets::get(const std::string & name) const
{
	const auto it = m_widgets.find(name);
	if (it == m_widgets.end())
		throw std::invalid_argument("Widget " + name + " does not exist");
	return it->second;
}

bool ui::gui::Widgets::has(const std::string & name) const
{
	return m_widgets.find(name) != m_widgets.end();
}
