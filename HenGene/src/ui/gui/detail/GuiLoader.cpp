
#include "GuiLoader.h"

#include "ui/gui/detail/WidgetLoader.h"

namespace
{
	constexpr const char * NODE_SCRIPT = "script";
	constexpr const char * NOTE_LAYOUT = "layout";

	constexpr const char * ATTR_SCRIPT_FILE = "file";
}

ui::gui::GuiLoader::GuiLoader(Gui & gui)
	: m_gui(&gui)
{}

void ui::gui::GuiLoader::load(const io::File & file)
{
	pugi::xml_document doc;
	doc.load_file(file.getPath().c_str());

	if (const auto node = doc.child(NODE_SCRIPT))
		loadScript(node);
	if (const auto node = doc.child(NOTE_LAYOUT))
		loadLayout(node);
}

void ui::gui::GuiLoader::loadScript(const pugi::xml_node & node)
{
	if (const auto attr = node.attribute(ATTR_SCRIPT_FILE))
		m_gui->getScript().execute(io::File{ attr.as_string() }.parse());
	if (const auto child = node.first_child())
		m_gui->getScript().execute(child.value());
}
void ui::gui::GuiLoader::loadLayout(const pugi::xml_node & node)
{
	WidgetLoader loader{ m_gui->getWidgets(), m_gui->getWidgets().get() };
	if (m_assets != nullptr)
		loader.inject(*m_assets);
	loader.load(node);
}
