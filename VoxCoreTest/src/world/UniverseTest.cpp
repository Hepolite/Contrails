
#include "CppUnitTest.h"

#include "logic/event/WorldEvents.h"
#include "world/Universe.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	TEST_CLASS(UniverseTest)
	{
	public:
		TEST_METHOD(Universe_createWorld)
		{
			bool created = false;
			logic::event::EventBus bus;
			bus.add<logic::event::WorldCreate>([&created](auto &) { created = true; });

			Universe universe;
			universe.inject(bus);
			universe.createWorld("name");

			Assert::IsTrue(created);
		}
		TEST_METHOD(Universe_destroyWorld)
		{
			bool destroyed = false;
			logic::event::EventBus bus;
			bus.add<logic::event::WorldDestroy>([&destroyed](auto &) { destroyed = true; });

			Universe universe;
			universe.inject(bus);
			universe.createWorld("name");
			universe.destroyWorld("name");

			Assert::IsTrue(destroyed);
		}

		TEST_METHOD(Universe_hasWorld)
		{
			Universe universe;

			Assert::IsFalse(universe.hasWorld("name"));
			universe.createWorld("name");
			Assert::IsTrue(universe.hasWorld("name"));
		}

		TEST_METHOD(Universe_getWorld)
		{
			Universe universe;
			universe.createWorld("worldA");
			universe.createWorld("worldB");

			const auto worldA = universe.getWorld("worldA");
			const auto worldB = universe.getWorld("worldB");
			const auto worldC = universe.getWorld("worldC");

			Assert::IsFalse(worldA == worldB);
			Assert::IsNotNull(worldA);
			Assert::IsNotNull(worldB);
			Assert::IsNull(worldC);
		}
	};
}