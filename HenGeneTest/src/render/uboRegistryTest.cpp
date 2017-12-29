
#include "CppUnitTest.h"

#include "render/uboRegistry.h"
#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	TEST_CLASS(uboRegistryTest)
	{
	public:
		TEST_METHOD(uboRegistry_has)
		{
			uboRegistry registry;
			registry.add("foo");

			Assert::IsFalse(registry.has("bar"));
			Assert::IsTrue(registry.has("foo"));
		}

		TEST_METHOD(uboRegistry_add)
		{
			uboRegistry registry;
			opengl::ubo & uboA = registry.add("fieldA");
			opengl::ubo & uboB = registry.add("fieldB");
			Assert::ExpectException<std::invalid_argument>([&registry]() { registry.add("fieldA"); });

			Assert::AreEqual(0u, uboA.getPort());
			Assert::AreEqual(1u, uboB.getPort());
		}
		TEST_METHOD(uboRegistry_get)
		{
			uboRegistry registry;
			opengl::ubo & ubo = registry.add("field");
			
			auto & uboRetrieved = registry.get("field");
			Assert::ExpectException<std::invalid_argument>([&registry]() { registry.get("foo"); });

			Assert::AreEqual(ubo.getHandle(), uboRetrieved.getHandle());
		}

		TEST_METHOD(uboRegistry_getBindings)
		{
			uboRegistry registry;
			auto & uboA = registry.add("a");
			auto & uboB = registry.add("b");

			const auto bindings = registry.getBindings();
			Assert::AreEqual(2u, bindings.size());
			Assert::AreEqual({ "a" }, bindings[0].first);
			Assert::AreEqual(uboA.getPort(), bindings[0].second);
			Assert::AreEqual({ "b" }, bindings[1].first);
			Assert::AreEqual(uboB.getPort(), bindings[1].second);
		}

	private:
		setup::Context m_context;
	};
}