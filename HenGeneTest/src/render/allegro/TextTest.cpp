
#include "CppUnitTest.h"

#include "asset/AssetRef.h"
#include "asset/AssetRegistry.h"
#include "asset/builtin/Font.h"
#include "asset/factory/FactoryFont.h"
#include "render/allegro/Text.h"
#include "io/File.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
	class data
	{
	public:
		data() { initialize(); }
		~data() { deinitialize(); }

		render::allegro::ComponentString build(const std::string & string, unsigned int size = 12u)
		{
			render::allegro::ComponentString component;
			component.setString(string);
			component.setFont(m_registry.get<render::allegro::Font>("font"));
			component.setSize(size);
			return component;
		}

	private:
		void initialize()
		{
			m_file.writeDangerous(asset::builtin::FONT_DATA, asset::builtin::FONT_SIZE);
			m_registry.add<render::allegro::Font>("font").m_factory = []()
			{
				auto asset = std::make_unique<render::allegro::Font>();
				asset::factory::LoaderFont{}.load(*asset, "font.ttf");
				return asset;
			};
		}
		void deinitialize() { m_file.erase(); }

		setup::Context m_context;
		asset::AssetRegistry m_registry;

		io::File m_file{ "font.ttf" };
	};

	class ComponentMock : public render::allegro::ComponentBase
	{
	public:
		virtual std::optional<render::allegro::Segment> calculateSegment(unsigned int index, int width) const override final
		{
			if (index != 0u)
				return std::nullopt;
			render::allegro::Segment segment;
			segment.m_endIndex = 1u;
			segment.m_draw = [&](auto, auto, auto) { m_drawn = true; };
			return std::make_optional(segment);
		}

		inline bool drawn() const { return m_drawn; }

	private:
		mutable bool m_drawn = false;
	};
}

namespace render
{
	namespace allegro
	{
		TEST_CLASS(ComponentStringTest)
		{
		public:
			TEST_METHOD(ComponentString_calculateComponent)
			{
				const auto component = m_data.build("Hello world!");
				const auto segA = component.calculateSegment(0u, 10000);
				const auto segB = component.calculateSegment(12u, 10000);

				Assert::IsTrue(segA.has_value());
				Assert::IsFalse(segB.has_value());

				Assert::AreEqual(0u, segA->m_startIndex);
				Assert::AreEqual(12u, segA->m_endIndex);
				Assert::AreNotEqual(0, segA->m_size.x);
				Assert::AreNotEqual(0, segA->m_size.y);
			}
			TEST_METHOD(ComponentString_calculateComponentWithNewLineChar)
			{
				const auto component = m_data.build("Hello\nWorld!");
				const auto segA = component.calculateSegment(0u, 10000);
				const auto segB = component.calculateSegment(6u, 10000);

				Assert::IsTrue(segA.has_value());
				Assert::IsTrue(segB.has_value());

				Assert::AreEqual(0u, segA->m_startIndex);
				Assert::AreEqual(6u, segA->m_endIndex);
				Assert::AreEqual(6u, segB->m_startIndex);
				Assert::AreEqual(12u, segB->m_endIndex);

				Assert::AreEqual(10000, segA->m_size.x);
				Assert::AreNotEqual(10000, segB->m_size.x);
			}
			TEST_METHOD(ComponentString_calculateComponentWithSmallBBox)
			{
				const auto component = m_data.build("Hello World!");
				const auto segA = component.calculateSegment(0u, 50);
				const auto segB = component.calculateSegment(6u, 50);

				Assert::IsTrue(segA.has_value());
				Assert::IsTrue(segB.has_value());

				Assert::AreEqual(0u, segA->m_startIndex);
				Assert::AreEqual(6u, segA->m_endIndex);
				Assert::AreEqual(6u, segB->m_startIndex);
				Assert::AreEqual(12u, segB->m_endIndex);

				Assert::AreEqual(50, segA->m_size.x);
			}
			TEST_METHOD(ComponentString_calculateComponentWithoutBreaks)
			{
				const auto component = m_data.build("Spectacular");
				const auto seg = component.calculateSegment(3u, 30);

				Assert::IsTrue(seg.has_value());

				Assert::AreEqual(30, seg->m_size.x);
				Assert::AreNotEqual(0u, seg->m_endIndex);
				Assert::AreNotEqual(3u, seg->m_endIndex);
			}
			TEST_METHOD(ComponentString_calculateComponentAlwaysProgresses)
			{
				const auto component = m_data.build("Word");
				const auto segA = component.calculateSegment(0u, 0);
				const auto segB = component.calculateSegment(1u, 0);
				const auto segC = component.calculateSegment(3u, 0);
				
				Assert::IsTrue(segA.has_value());
				Assert::IsTrue(segB.has_value());
				Assert::IsTrue(segC.has_value());

				Assert::AreEqual(1u, segA->m_endIndex);
				Assert::AreEqual(2u, segB->m_endIndex);
				Assert::AreEqual(4u, segC->m_endIndex);
			}

		private:
			data m_data;
		};

		TEST_CLASS(TextTest)
		{
		public:
			TEST_METHOD(Text_add)
			{
				Text text;
				text.add<ComponentString>() = m_data.build("String component");

				Assert::AreEqual(1u, text.size());
				Assert::IsFalse(text.empty());
			}
			
			TEST_METHOD(Text_calculateLine)
			{
				Text text;
				text.add<ComponentString>() = m_data.build("Hello ");
				text.add<ComponentString>() = m_data.build("World!");
				const auto lineA = text.calculateLine(0u, 0u, 1000000);
				const auto lineB = text.calculateLine(2u, 0u, 1000000);

				Assert::IsTrue(lineA.has_value());
				Assert::IsFalse(lineB.has_value());

				Assert::AreEqual(0u, lineA->m_startComponent);
				Assert::AreEqual(2u, lineA->m_endComponent);
				Assert::AreEqual(0u, lineA->m_startIndex);
				Assert::AreEqual(0u, lineA->m_endIndex);
				Assert::AreNotEqual(0, lineA->m_size.x);
				Assert::AreNotEqual(0, lineA->m_size.y);
			}
			TEST_METHOD(Text_calculateLineWithNewLineChar)
			{
				Text text;
				text.add<ComponentString>() = m_data.build("Hello\nWorld!");
				const auto lineA = text.calculateLine(0u, 0u, 10000);
				const auto lineB = text.calculateLine(0u, 6u, 10000);

				Assert::IsTrue(lineA.has_value());
				Assert::IsTrue(lineB.has_value());

				Assert::AreEqual(0u, lineA->m_startComponent);
				Assert::AreEqual(0u, lineA->m_startIndex);
				Assert::AreEqual(0u, lineA->m_endComponent);
				Assert::AreEqual(6u, lineA->m_endIndex);
				Assert::AreEqual(10000, lineA->m_size.x);

				Assert::AreEqual(0u, lineB->m_startComponent);
				Assert::AreEqual(6u, lineB->m_startIndex);
				Assert::AreEqual(1u, lineB->m_endComponent);
				Assert::AreEqual(0u, lineB->m_endIndex);
				Assert::AreNotEqual(10000, lineB->m_size.x);
			}
			TEST_METHOD(Text_calculateLineWithSmallBBox)
			{
				Text text;
				text.add<ComponentString>() = m_data.build("Hello World!");
				const auto lineA = text.calculateLine(0u, 0u, 50);
				const auto lineB = text.calculateLine(0u, 6u, 50);

				Assert::IsTrue(lineA.has_value());
				Assert::IsTrue(lineB.has_value());

				Assert::AreEqual(0u, lineA->m_startComponent);
				Assert::AreEqual(0u, lineA->m_startIndex);
				Assert::AreEqual(0u, lineA->m_endComponent);
				Assert::AreEqual(6u, lineA->m_endIndex);
				Assert::AreEqual(50, lineA->m_size.x);

				Assert::AreEqual(0u, lineB->m_startComponent);
				Assert::AreEqual(6u, lineB->m_startIndex);
				Assert::AreEqual(1u, lineB->m_endComponent);
				Assert::AreEqual(0u, lineB->m_endIndex);
			}
			TEST_METHOD(Text_calculateLineWithoutBreaks)
			{
				Text text;
				text.add<ComponentString>() = m_data.build("Spectacular");
				const auto line = text.calculateLine(0u, 3u, 30);

				Assert::IsTrue(line.has_value());

				Assert::AreEqual(30, line->m_size.x);
				Assert::AreEqual(0u, line->m_endComponent);
				Assert::AreNotEqual(0u, line->m_endIndex);
				Assert::AreNotEqual(3u, line->m_endIndex);
			}

			TEST_METHOD(Text_draw)
			{
				Text text;
				const auto & component = text.add<ComponentMock>();
				text.draw({}, 0.0_s);

				Assert::IsTrue(component.drawn());
			}

		private:
			data m_data;
		};
	}
}