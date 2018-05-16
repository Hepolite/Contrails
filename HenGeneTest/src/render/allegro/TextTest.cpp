
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

namespace render
{
	namespace allegro
	{
		TEST_CLASS(ComponentStringTest)
		{
		public:
			ComponentStringTest() { initialize(); }
			~ComponentStringTest() { deinitialize(); }

			TEST_METHOD(ComponentString_calculateComponent)
			{
				const auto component = build("Hello world!");
				const auto opSegA = component.calculateSegment(0u, { 0, 0 }, { 0, 0, 10000, 10000 });
				const auto opSegB = component.calculateSegment(12u, { 0, 0 }, { 0, 0, 10000, 10000 });

				Assert::IsTrue(opSegA.has_value());
				Assert::IsFalse(opSegB.has_value());

				Assert::AreEqual(0u, opSegA->m_startIndex);
				Assert::AreEqual(12u, opSegA->m_endIndex);
				Assert::AreEqual({ 0, 0 }, opSegA->m_pos);
				Assert::AreNotEqual(0, opSegA->m_size.x);
				Assert::AreNotEqual(0, opSegA->m_size.y);
			}
			TEST_METHOD(ComponentString_calculateComponentWithNewLine)
			{
				const auto component = build("Hello\nWorld!");
				const auto opSegA = component.calculateSegment(0u, { 0, 0 }, { 0, 0, 10000, 10000 });
				const auto opSegB = component.calculateSegment(6u, { 0, 0 }, { 0, 0, 10000, 10000 });
				const auto opSegC = component.calculateSegment(12u, { 0, 0 }, { 0, 0, 10000, 10000 });

				Assert::IsTrue(opSegA.has_value());
				Assert::IsTrue(opSegB.has_value());
				Assert::IsFalse(opSegC.has_value());

				Assert::AreEqual(0u, opSegA->m_startIndex);
				Assert::AreEqual(6u, opSegA->m_endIndex);
				Assert::AreEqual(6u, opSegB->m_startIndex);
				Assert::AreEqual(12u, opSegB->m_endIndex);
				Assert::AreEqual(10000, opSegA->m_size.x);
			}
			TEST_METHOD(ComponentString_calculateComponentWithSmallBox)
			{
				const auto component = build("Hello.World!");
				const auto opSegA = component.calculateSegment(0u, { 0, 0 }, { 0, 0, 40, 100 });
				const auto opSegB = component.calculateSegment(6u, { 0, 0 }, { 0, 0, 40, 100 });
				const auto opSegC = component.calculateSegment(12u, { 0, 0 }, { 0, 0, 40, 100 });

				Assert::IsTrue(opSegA.has_value());
				Assert::IsTrue(opSegB.has_value());
				Assert::IsFalse(opSegC.has_value());

				Assert::AreEqual(0u, opSegA->m_startIndex);
				Assert::AreEqual(6u, opSegA->m_endIndex);
				Assert::AreEqual(6u, opSegB->m_startIndex);
				Assert::AreEqual(12u, opSegB->m_endIndex);
			}

		private:
			void initialize()
			{
				m_file.writeDangerous(asset::builtin::FONT_DATA, asset::builtin::FONT_SIZE);
				m_registry.add<Font>("font").m_factory = []()
				{
					auto asset = std::make_unique<Font>();
					asset::factory::LoaderFont{}.load(*asset, "font.ttf");
					return asset;
				};
			}
			void deinitialize() { m_file.erase(); }

			ComponentString build(const std::string & string, unsigned int size = 12u)
			{
				ComponentString component;
				component.setString(string);
				component.setFont(m_registry.get<Font>("font"));
				component.setSize(size);
				return component;
			}

			setup::Context m_context;
			asset::AssetRegistry m_registry;

			io::File m_file{ "font.ttf" };
		};

		TEST_CLASS(TextTest)
		{
		public:
			TEST_METHOD(Text_sanity)
			{
				Assert::IsTrue(true);
			}
		};
	}
}