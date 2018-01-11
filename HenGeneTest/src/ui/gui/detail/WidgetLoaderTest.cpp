
#include "CppUnitTest.h"

#include "asset/AssetRegistry.h"
#include "ui/gui/detail/WidgetLoader.h"
#include "ui/Keyboard.h"

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
				Widgets widgets;
				Widget widgetA;
				Widget widgetB;
				WidgetLoader{ widgets, widgetA }.loadActivation(m_doc.child("activation"));
				WidgetLoader{ widgets, widgetB }.loadActivation({});

				Assert::IsTrue(widgetA.m_activation.m_locked);
				Assert::IsFalse(widgetB.m_activation.m_locked);
				Assert::AreEqual(ALLEGRO_KEY_H | 0, widgetA.m_activation.m_key);
				Assert::AreEqual(ALLEGRO_KEYMOD_CTRL | ALLEGRO_KEYMOD_SHIFT, widgetA.m_activation.m_mask);
				Assert::AreEqual(-1, widgetB.m_activation.m_key);
				Assert::AreEqual(0, widgetB.m_activation.m_mask);
			}
			TEST_METHOD(WidgetLoader_loadAssets)
			{
				asset::AssetRegistry registry;
				Widget widget;
				WidgetLoader loader{ Widgets{}, widget };
				loader.inject(registry);
				loader.loadAssets(m_doc.child("assets"));

				Assert::AreEqual(2u, widget.m_assets.m_sprites.size());
				Assert::IsFalse(widget.m_assets.m_sprites.find("icon") == widget.m_assets.m_sprites.end());
				Assert::IsFalse(widget.m_assets.m_sprites.find("background") == widget.m_assets.m_sprites.end());
				Assert::AreEqual(1u, widget.m_assets.m_scripts.size());
				Assert::AreEqual({ "def func() { return 3 + 5; }" }, widget.m_assets.m_scripts["initialize"]);
			}
			TEST_METHOD(WidgetLoader_loadBorder)
			{
				Widgets widgets;
				Widget widgetA;
				Widget widgetB;
				WidgetLoader{ widgets, widgetA }.loadBorder(m_doc.child("border"));
				WidgetLoader{ widgets, widgetB }.loadBorder({});

				Assert::AreEqual({ 5.0f, 5.0f, 2.0f, 5.0f }, widgetA.m_border.m_inner);
				Assert::AreEqual({ 4.0f, 3.0f, 3.0f, 3.0f }, widgetA.m_border.m_outer);
				Assert::AreEqual({ 0.0f, 0.0f, 0.0f, 0.0f }, widgetB.m_border.m_inner);
				Assert::AreEqual({ 0.0f, 0.0f, 0.0f, 0.0f }, widgetB.m_border.m_outer);
			}
			TEST_METHOD(WidgetLoader_loadFamily)
			{
				Widgets widgets;
				Widget widget;
				WidgetLoader loader{ widgets, widget };
				loader.loadFamily(m_doc);

				Assert::IsTrue(widgets.has("child"));
				Assert::IsTrue(widgets.get("child").m_header.m_name == "child");
				Assert::IsTrue(widgets.get("child").m_link.m_location == Link::Location::CENTER);
			}
			TEST_METHOD(WidgetLoader_loadGroup)
			{
				Widgets widgets;
				Widget & widgetL = widgets.create("widgetL");
				Widget & widgetA = widgets.create("widgetA");
				Widget & widgetB = widgets.create("widgetB");
				WidgetLoader{ widgets, widgetL }.loadGroup({});
				WidgetLoader{ widgets, widgetA }.loadGroup(m_doc.child("group"));
				WidgetLoader{ widgets, widgetB }.loadGroup({});

				Assert::IsTrue(widgetL.m_group.m_leader.empty());
				Assert::AreEqual(2u, widgetL.m_group.m_members.size());
				Assert::IsFalse(widgetL.m_group.m_members.find("widgetL") == widgetL.m_group.m_members.end());
				Assert::IsFalse(widgetL.m_group.m_members.find("widgetA") == widgetL.m_group.m_members.end());

				Assert::AreEqual({ "widgetL" }, widgetA.m_group.m_leader);
				Assert::IsTrue(widgetA.m_group.m_members.empty());

				Assert::IsTrue(widgetB.m_group.m_leader.empty());
				Assert::AreEqual(1u, widgetB.m_group.m_members.size());
				Assert::IsFalse(widgetB.m_group.m_members.find("widgetB") == widgetB.m_group.m_members.end());
			}
			TEST_METHOD(WidgetLoader_loadHeader)
			{
				Widgets widgets;
				Widget widgetA;
				Widget widgetB;
				WidgetLoader{ widgets, widgetA }.loadHeader(m_doc.child("widget"));
				WidgetLoader{ widgets, widgetB }.loadHeader({});

				Assert::IsFalse(widgetA.m_render.m_visible);
				Assert::IsTrue(widgetB.m_render.m_visible);
			}
			TEST_METHOD(WidgetLoader_loadLink)
			{
				Widgets widgets;
				widgets.create("widgetP");
				Widget & widgetA = widgets.create("widgetA", "widgetP");
				Widget & widgetB = widgets.create("widgetB", "widgetP");
				WidgetLoader{ widgets, widgetA }.loadLink(m_doc.child("link"));
				WidgetLoader{ widgets, widgetB }.loadLink({});

				Assert::AreEqual({ "widgetTarget" }, widgetA.m_link.m_target);
				Assert::IsTrue(Link::Location::RIGHT_BOTTOM == widgetA.m_link.m_location);
				Assert::AreEqual({ "widgetP" }, widgetB.m_link.m_target);
				Assert::IsTrue(Link::Location::TOP_LEFT == widgetB.m_link.m_location);
			}
			TEST_METHOD(WidgetLoader_loadPosition)
			{
				Widgets widgets;
				Widget widgetA;
				Widget widgetB;
				WidgetLoader{ widgets, widgetA }.loadPosition(m_doc.child("position"));
				WidgetLoader{ widgets, widgetB }.loadPosition({});

				Assert::IsFalse(widgetA.m_position.m_automatic);
				Assert::AreEqual({ 64, 48 }, widgetA.m_position.m_pos);
				Assert::IsTrue(widgetB.m_position.m_automatic);
				Assert::AreEqual({ 0, 0 }, widgetB.m_position.m_pos);
			}
			TEST_METHOD(WidgetLoader_loadSize)
			{
				Widgets widgets;
				Widget widgetA;
				Widget widgetB;
				WidgetLoader{ widgets, widgetA }.loadSize(m_doc.child("size"));
				WidgetLoader{ widgets, widgetB }.loadSize({});

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
				Widgets widgets;
				Widget widgetA;
				Widget widgetB;
				WidgetLoader{ widgets, widgetA }.loadState(m_doc.child("state"));
				WidgetLoader{ widgets, widgetB }.loadState({});

				Assert::AreEqual(true, widgetA.m_state.m_bool);
				Assert::AreEqual(3.14f, widgetA.m_state.m_float);
				Assert::AreEqual({ "Hello World!" }, widgetA.m_state.m_string);
				Assert::AreEqual(false, widgetB.m_state.m_bool);
				Assert::AreEqual(0.0f, widgetB.m_state.m_float);
				Assert::AreEqual({ "" }, widgetB.m_state.m_string);
			}

		private:
			void initialize()
			{
				auto activation = m_doc.append_child("activation");
				activation.append_attribute("locked").set_value(true);
				activation.append_attribute("key").set_value("ctrl+shift+H");

				auto family = m_doc.append_child("widget");
				family.append_attribute("name").set_value("child");
				family.append_attribute("type").set_value("button");
				family.append_attribute("visible").set_value("false");
				family.append_child("link").append_attribute("location").set_value("center");

				auto group = m_doc.append_child("group");
				group.append_attribute("leader").set_value("widgetL");

				auto assets = m_doc.append_child("assets");
				auto assetSprite = assets.append_child("sprites");
				assetSprite.append_attribute("icon").set_value("sprites/icon");
				assetSprite.append_attribute("background").set_value("sprites/background");
				auto assetScript = assets.append_child("scripts");
				assetScript.append_attribute("initialize").set_value("def func() { return 3 + 5; }");

				auto border = m_doc.append_child("border");
				border.append_attribute("all").set_value("5");
				border.append_attribute("outer").set_value("3");
				border.append_attribute("outer_left").set_value("4");
				border.append_attribute("inner_top").set_value("2");

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
				state.append_attribute("bool").set_value("true");
				state.append_attribute("float").set_value("3.14");
				state.append_attribute("string").set_value("Hello World!");
			}

			pugi::xml_document m_doc;
		};
	}
}