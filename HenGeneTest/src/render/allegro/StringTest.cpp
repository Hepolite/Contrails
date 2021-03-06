
#include "CppUnitTest.h"

#include "render/allegro/String.h"

#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace allegro
	{
		TEST_CLASS(StringTest)
		{
		public:
			TEST_METHOD(String_ctor)
			{
				const String stringA;
				const String stringB{ "Hello World!" };

				Assert::AreEqual({ "" }, stringA.getString());
				Assert::AreEqual({ "Hello World!" }, stringB.getString());
			}
			TEST_METHOD(String_copy)
			{
				const String tmpA{ "Foo" }, tmpB{ "Baz" };
				const String copyA{ tmpA };
				String copyB{ "Bar" }; copyB = tmpB;

				Assert::AreEqual({ "Foo" }, copyA.getString());
				Assert::AreEqual({ "Baz" }, copyB.getString());
			}
			TEST_METHOD(String_move)
			{
				String tmpA{ "Foo" }, tmpB{ "Baz" };
				const String moveA{ std::move(tmpA) };
				String moveB{ "Bar" }; moveB = std::move(tmpB);

				Assert::AreEqual({ "Foo" }, moveA.getString());
				Assert::AreEqual({ "Baz" }, moveB.getString());
			}

			TEST_METHOD(String_length)
			{
				Assert::AreEqual(0u, String{}.length());
				Assert::AreEqual(5u, String{ "Hello" }.length());
				Assert::AreEqual(2u, String{ "��" }.length());
			}
			TEST_METHOD(String_at)
			{
				const String string{ "Hello!" };

				Assert::AreEqual(static_cast<unsigned int>('H'), string.at(0u));
				Assert::AreEqual(static_cast<unsigned int>('!'), string.at(5u));
				Assert::AreEqual(static_cast<unsigned int>('\0'), string.at(6u));
			}
			TEST_METHOD(String_next)
			{
				const String string{ "Te" };
				unsigned int index = 0u;

				Assert::AreEqual(static_cast<unsigned int>('T'), string.next(index));
				Assert::AreEqual(1u, index);
				Assert::AreEqual(static_cast<unsigned int>('e'), string.next(index));
				Assert::AreEqual(2u, index);
				Assert::AreEqual(static_cast<unsigned int>('\0'), string.next(index));
				Assert::AreEqual(2u, index);
			}
			
			TEST_METHOD(String_find)
			{
				const String string{ "Hello World!" };

				Assert::AreEqual(0u, string.find('H'));
				Assert::AreEqual(2u, string.find('l'));
				Assert::AreEqual(4u, string.find('o', 4u));
				Assert::AreEqual(9u, string.find('l', 4u));
				Assert::AreEqual(12u, string.find('\0'));

				Assert::AreEqual(String::END, string.find('x'));
				Assert::AreEqual(String::END, string.find('e', 2u));
				Assert::AreEqual(String::END, string.find('W', String::END));
			}
			TEST_METHOD(String_substr)
			{
				const String string{ "Hello World!" };
				
				Assert::AreEqual({ "Hello World!" }, string.substr().getString());
				Assert::AreEqual({ "World!" }, string.substr(6u).getString());
				Assert::AreEqual({ "ello W" }, string.substr(1u, 7u).getString());
				Assert::AreEqual({ "" }, string.substr(String::END).getString());
			}

		private:
			setup::Context m_context;
		};
	}
}