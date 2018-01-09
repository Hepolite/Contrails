
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
				Widget widgetA;
				Widget widgetB;
				WidgetLoader{}.loadActivation(widgetA, m_doc.child("activation"));
				WidgetLoader{}.loadActivation(widgetB, {});

				Assert::AreEqual(ALLEGRO_KEY_H | 0, widgetA.m_activation.m_key);
				Assert::AreEqual(ALLEGRO_KEYMOD_CTRL | ALLEGRO_KEYMOD_SHIFT, widgetA.m_activation.m_mask);
				Assert::AreEqual(-1, widgetB.m_activation.m_key);
				Assert::AreEqual(0, widgetB.m_activation.m_mask);
			}
			TEST_METHOD(WidgetLoader_loadAssets)
			{
				asset::AssetRegistry registry;
				Widget widget;
				WidgetLoader loader;
				loader.inject(registry);
				loader.loadAssets(widget, m_doc.child("assets"));

				Assert::AreEqual(2u, widget.m_assets.m_sprites.size());
				Assert::IsFalse(widget.m_assets.m_sprites.find("icon") == widget.m_assets.m_sprites.end());
				Assert::IsFalse(widget.m_assets.m_sprites.find("background") == widget.m_assets.m_sprites.end());
				Assert::AreEqual(1u, widget.m_assets.m_scripts.size());
				Assert::AreEqual({ "def func() { return 3 + 5; }" }, widget.m_assets.m_scripts["initialize"]);
			}
			TEST_METHOD(WidgetLoader_loadBorder)
			{
				Widget widgetA;
				Widget widgetB;
				WidgetLoader{}.loadBorder(widgetA, m_doc.child("border"));
				WidgetLoader{}.loadBorder(widgetB, {});

				Assert::AreEqual({ 5.0f, 5.0f, 2.0f, 5.0f }, widgetA.m_border.m_inner);
				Assert::AreEqual({ 4.0f, 3.0f, 3.0f, 3.0f }, widgetA.m_border.m_outer);
				Assert::AreEqual({ 0.0f, 0.0f, 0.0f, 0.0f }, widgetB.m_border.m_inner);
				Assert::AreEqual({ 0.0f, 0.0f, 0.0f, 0.0f }, widgetB.m_border.m_outer);
			}
			TEST_METHOD(WidgetLoader_loadFamily)
			{
				Assert::Fail();
			}
			TEST_METHOD(WidgetLoader_loadGroup)
			{
				Assert::Fail();
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
				WidgetLoader{}.loadPosition(widgetB, {});

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
				WidgetLoader{}.loadSize(widgetB, {});

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
				WidgetLoader{}.loadState(widgetB, {});

				Assert::IsTrue(widgetA.m_state.m_locked);
				Assert::IsFalse(widgetB.m_state.m_locked);
				Assert::IsTrue(widgetA.m_state.m_value == "3.14");
				Assert::IsTrue(widgetB.m_state.m_value.empty());
			}

		private:
			void initialize()
			{
				auto activation = m_doc.append_child("activation");
				activation.append_attribute("key").set_value("ctrl+shift+H");

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
				state.append_attribute("locked").set_value(true);
				state.append_attribute("value").set_value("3.14");
			}

			pugi::xml_document m_doc;
		};
	}
}