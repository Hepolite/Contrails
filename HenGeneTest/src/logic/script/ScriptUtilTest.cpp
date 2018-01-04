
#include "CppUnitTest.h"

#include "logic/script/ScriptUtil.h"

#include <functional>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace
{
	enum class FooBar { A, B, C };

	class MockParent {};
	class Mock : public MockParent
	{
	public:
		Mock() = default;
		Mock(const std::string & field) : m_field(field) {}
		~Mock() = default;

		bool foo() { return true; }
		bool bar() const { return true; }
		bool bar(int) const { return false; }

		std::string m_field = "Hello World!";
	};

	void baz(int i, int j) {}
}

namespace logic
{
	namespace script
	{
		TEST_CLASS(ScriptUtilTest)
		{
		public:
			TEST_METHOD(ScriptUtil_scriptData)
			{
				util::registerScriptData([](Script & script) { util::addVar(script, 42, "answer"); });

				Script script;
				Assert::AreEqual(42, util::get<int>(script, "answer"));
			}

			TEST_METHOD(ScriptUtil_add)
			{
				int var = 42;
				const std::string varConst = "Greetings";
				float varGlobal = 3.14f;
				const double varGlobalConst = 1337.0;

				Script script;

				util::addEnum<FooBar>(script, "FooBar", { { FooBar::A, "A" }, { FooBar::B, "B" }, { FooBar::C, "C" } });
				util::addType<Mock>(script, "Mock");
				util::addRelation<MockParent, Mock>(script);

				util::addVar(script, &var, "v");
				util::addVar(script, 7, "vf");
				util::addVarConst(script, &varConst, "vc");
				util::addVarGlobal(script, &varGlobal, "vg");
				util::addVarGlobal(script, 6115.5f, "vgf");
				util::addVarGlobalConst(script, &varGlobalConst, "vgc");
				util::addAttribute(script, &Mock::m_field, "a");

				util::addCtor<Mock()>(script, "Mock");
				util::addCtor<Mock(const std::string &)>(script, "Mock");
				util::addFun(script, &Mock::foo, "foo");
				util::addFun<Mock, bool>(script, &Mock::bar, "bar");
				util::addFun<Mock, bool, int>(script, &Mock::bar, "bar");
				util::addFun(script, &baz, "baz");
			}

			TEST_METHOD(ScriptUtil_execute)
			{
				Script script;

				Assert::IsTrue(util::execute(script, "def foo(a, b) { return a + b; }"));
				Assert::IsFalse(util::execute(script, "malformed code"));

				const auto shellA = util::get<std::function<int(int, int)>>(script, "foo");
				const auto shellB = util::get<std::function<void()>>(script, "bar");

				Assert::AreEqual(4, util::execute(script, shellA, 1, 3));
				Assert::IsFalse(util::execute(script, shellB));
			}
		};
	}
}