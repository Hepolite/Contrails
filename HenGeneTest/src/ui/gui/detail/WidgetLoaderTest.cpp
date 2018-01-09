
#include "CppUnitTest.h"

#include "ui/gui/detail/WidgetLoader.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	namespace gui
	{
		TEST_CLASS(WidgetLoaderTest)
		{
		public:
			WidgetLoaderTest() { initialize(); }

			TEST_METHOD(WidgetLoader_loadActivation)
			{
			}
			TEST_METHOD(WidgetLoader_loadAssets)
			{
			}
			TEST_METHOD(WidgetLoader_loadBorder)
			{
			}
			TEST_METHOD(WidgetLoader_loadFamily)
			{
			}
			TEST_METHOD(WidgetLoader_loadGroup)
			{
			}
			TEST_METHOD(WidgetLoader_loadLink)
			{
				Widget widgetA;
				Widget widgetB;
				widgetA.m_family.m_parent = "widgetP";
				widgetB.m_family.m_parent = "widgetP";
				WidgetLoader{}.loadLink(widgetA, m_doc.child("link"));
				WidgetLoader{}.loadLink(widgetB, {});

				Assert::AreEqual({ "widgetTarget" }, widgetA.m_link.m_target);
				Assert::IsTrue(Link::Location::RIGHT_BOTTOM == widgetA.m_link.m_location);
				Assert::AreEqual({ "widgetP" }, widgetB.m_link.m_target);
				Assert::IsTrue(Link::Location::TOP_LEFT == widgetB.m_link.m_location);
			}
			TEST_METHOD(WidgetLoader_loadPosition)
			{
				Widget widgetA;
				Widget widgetB;
				WidgetLoader{}.loadPosition(widgetA, m_doc.child("position"));
				WidgetLoader{}.loadLink(widgetB, {});

				Assert::IsFalse(widgetA.m_position.m_automatic);
				Assert::AreEqual({ 64, 48 }, widgetA.m_position.m_pos);
				Assert::IsTrue(widgetB.m_position.m_automatic);
				Assert::AreEqual({ 0, 0 }, widgetB.m_position.m_pos);
			}
			TEST_METHOD(WidgetLoader_loadSize)
			{
				Widget widgetA;
				Widget widgetB;
				WidgetLoader{}.loadSize(widgetA, m_doc.child("size"));
				WidgetLoader{}.loadLink(widgetB, {});

				Assert::IsFalse(widgetA.m_size.m_automatic);
				Assert::AreEqual({ 128, 32 }, widgetA.m_size.m_minSize);
				Assert::AreEqual({ 256, 48 }, widgetA.m_size.m_maxSize);
				Assert::AreEqual({ 160, 40 }, widgetA.m_size.m_size);
				Assert::IsTrue(widgetB.m_size.m_automatic);
				Assert::AreEqual({ 0, 0 }, widgetB.m_size.m_minSize);
				Assert::AreEqual(glm::vec2{ std::numeric_limits<float>::max() }, widgetB.m_size.m_maxSize);
				Assert::AreEqual({ 0, 0 }, widgetB.m_size.m_size);
			}
			TEST_METHOD(WidgetLoader_loadState)
			{
				Widget widgetA;
				Widget widgetB;
				WidgetLoader{}.loadState(widgetA, m_doc.child("state"));
				WidgetLoader{}.loadLink(widgetB, {});

				Assert::IsTrue(widgetA.m_state.m_locked);
				Assert::IsFalse(widgetB.m_state.m_locked);
				Assert::IsTrue(widgetA.m_state.m_value == "3.14");
				Assert::IsTrue(widgetB.m_state.m_value.empty());
			}

		private:
			void initialize()
			{
				auto link = m_doc.append_child("link");
				link.append_attribute("target").set_value("widgetTarget");
				link.append_attribute("location").set_value("right_bottom");

				auto position = m_doc.append_child("position");
				position.append_child(pugi::node_pcdata).set_value("64 48");

				auto size = m_doc.append_child("size");
				size.append_attribute("min").set_value("128 32");
				size.append_attribute("max").set_value("256 48");
				size.append_child(pugi::node_pcdata).set_value("160 40");

				auto state = m_doc.append_child("state");
				state.append_attribute("locked").set_value(true);
				state.append_attribute("value").set_value("3.14");
			}

			pugi::xml_document m_doc;
		};
	}
}