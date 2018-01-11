
#include "CppUnitTest.h"

#include "ui/gui/detail/WidgetLoader.h"
#include "ui/gui/detail/WidgetProcessor.h"

#include <glm/Unittest.h>
#include <pugixml/pugixml.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	namespace gui
	{
		constexpr const char * PARENT = "parent";
		constexpr const char * CHILD_A = "childA";
		constexpr const char * CHILD_B = "childB";
		constexpr const char * CHILD_C = "childC";

		TEST_CLASS(WidgetProcessorTest)
		{
		public:
			WidgetProcessorTest() { initialize(); }

			TEST_METHOD(WidgetProcessor_validateSetup)
			{
				Assert::IsTrue(m_widgets.has(PARENT));
				Assert::IsTrue(m_widgets.has(CHILD_A));
				Assert::IsTrue(m_widgets.has(CHILD_B));
				Assert::IsTrue(m_widgets.has(CHILD_C));
				Assert::AreEqual(3u, m_widgets.get(PARENT).m_family.m_children.size());
				Assert::AreEqual({ PARENT }, m_widgets.get(CHILD_A).m_family.m_parent);
				Assert::AreEqual({ PARENT }, m_widgets.get(CHILD_B).m_family.m_parent);
				Assert::AreEqual({ PARENT }, m_widgets.get(CHILD_C).m_family.m_parent);
			}

			TEST_METHOD(WidgetProcessor_getParent)
			{
				Processor processor{ m_widgets, m_widgets.get(CHILD_A) };
				Assert::AreEqual({ PARENT }, processor.getParent().m_header.m_name);
			}
			TEST_METHOD(WidgetProcessor_getChild)
			{
				Processor processorChild{ m_widgets, m_widgets.get(CHILD_A) };
				Processor processorParent{ m_widgets, m_widgets.get(PARENT) };
				Assert::ExpectException<std::invalid_argument>([&processorChild]() { processorChild.getChild(CHILD_B); });
				Assert::AreEqual({ CHILD_A }, processorParent.getChild(CHILD_A).m_header.m_name);
				Assert::AreEqual({ CHILD_B }, processorParent.getChild(CHILD_B).m_header.m_name);
				Assert::AreEqual({ CHILD_C }, processorParent.getChild(CHILD_C).m_header.m_name);
			}

			TEST_METHOD(WidgetProcessor_process)
			{
				const auto & childA = getAndProcess(CHILD_A);
				const auto & childB = getAndProcess(CHILD_B);
				const auto & parent = getAndProcess(PARENT);
				const auto & childC = getAndProcess(CHILD_C);

				Assert::AreEqual({ 3.0f, 4.0f }, childA.m_position.m_pos);
				Assert::AreEqual({ 16.0f, 16.0f }, childA.m_size.m_size);
				Assert::AreEqual({ 24.0f, 8.0f }, childB.m_position.m_pos);
				Assert::AreEqual({ 16.0f, 8.0f }, childB.m_size.m_size);
				Assert::AreEqual({ 33.0f, 4.0f }, childC.m_position.m_pos);
				Assert::AreEqual({ 8.0f, 16.0f }, childC.m_size.m_size);
				Assert::AreEqual({ 0.0f, 0.0f }, parent.m_position.m_pos);
				Assert::AreEqual({ 45.0f, 28.0f }, parent.m_size.m_size);
			}
			TEST_METHOD(WidgetProcessor_calculatePosition)
			{
				Assert::AreEqual({ 0.0f, 0.0f }, Processor{ m_widgets, m_widgets.get(PARENT) }.calculatePosition());
				Assert::AreEqual({ 3.0f, 4.0f }, Processor{ m_widgets, m_widgets.get(CHILD_A) }.calculatePosition());
				Assert::AreEqual({ 21.0f, 4.0f }, Processor{ m_widgets, m_widgets.get(CHILD_B) }.calculatePosition());
			}
			TEST_METHOD(WidgetProcessor_calculateSize)
			{
				getAndProcess(CHILD_A);
				getAndProcess(CHILD_B);
				getAndProcess(CHILD_C);
				Assert::AreEqual({ 45.0f, 28.0f }, Processor{ m_widgets, m_widgets.get(PARENT) }.calculateSize());
			}

		private:
			void initialize();
			void appendAttribute(pugi::xml_node & node, const std::unordered_map<std::string, std::string> & attributes);

			Widget & getAndProcess(const std::string widget);

			pugi::xml_document m_doc;
			Widgets m_widgets;
		};
	}
}

void ui::gui::WidgetProcessorTest::initialize()
{
	auto parent = m_doc.append_child("widget");
	appendAttribute(parent, { { "name", PARENT } });
	appendAttribute(parent.append_child("border"), { { "inner", "3" }, { "inner_top", "4" }, { "inner_bottom", "8" } });

	auto childA = parent.append_child("widget");
	appendAttribute(childA, { { "name", CHILD_A } });
	appendAttribute(childA.append_child("border"), { { "all", "2" } });
	childA.append_child("size").append_child(pugi::node_pcdata).set_value("16 16");

	auto childB = parent.append_child("widget");
	appendAttribute(childB, { { "name", CHILD_B } });
	appendAttribute(childB.append_child("border"), { { "all", "5" } });
	appendAttribute(childB.append_child("link"), { { "target", "childA" }, { "location", "right" } });
	childB.append_child("size").append_child(pugi::node_pcdata).set_value("16 8");

	auto childC = parent.append_child("widget");
	appendAttribute(childC, { { "name", CHILD_C } });
	appendAttribute(childC.append_child("border"), { { "all", "4" } });
	appendAttribute(childC.append_child("link"), { { "location", "bottom_right" } });
	appendAttribute(childC.append_child("size"), { { "min", "8 16" } });

	WidgetLoader{ m_widgets, m_widgets.get("") }.load(m_doc);
}
void ui::gui::WidgetProcessorTest::appendAttribute(pugi::xml_node & node, const std::unordered_map<std::string, std::string>& attributes)
{
	for (const auto it : attributes)
		node.append_attribute(it.first.c_str()).set_value(it.second.c_str());
}

ui::gui::Widget & ui::gui::WidgetProcessorTest::getAndProcess(const std::string widget)
{
	auto & w = m_widgets.get(widget);
	w.m_logic.m_process();
	return w;
}
