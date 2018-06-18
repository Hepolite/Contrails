
#include "CppUnitTest.h"

#include "logic/event/EventBus.h"
#include "world/io/UniverseSaver.h"
#include "world/World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace io
	{
		TEST_CLASS(UniverseSaverTest)
		{
		public:
			~UniverseSaverTest() { ::io::Folder{ "worlds" }.erase(true); }

			TEST_METHOD(UniverseSaver_open)
			{
				World worldA{ "world_name" };
				World worldB{ "world_other" };
				World worldC{ "world_other" };
				UniverseSaver saver{ "worlds" };

				Assert::IsTrue(saver.open(worldA));
				Assert::IsTrue(saver.open(worldB));
				Assert::IsFalse(saver.open(worldC));
			}
			TEST_METHOD(UniverseSaver_close)
			{
				World worldA{ "worldA" };
				World worldB{ "worldB" };
				UniverseSaver saver{ "worlds" };
				saver.open(worldA);

				Assert::IsTrue(saver.close(worldA));
				Assert::IsFalse(saver.close(worldA));
				Assert::IsFalse(saver.close(worldB));
			}

			TEST_METHOD(UniverseSaver_saveWorld)
			{
				logic::event::EventBus bus;
				World world;
				world.inject(bus);

				UniverseSaver saver{ "worlds" };
				saver.inject(bus);
				saver.open(world);
				world.write({ 1700, -200, 2500 }, data::BlockData{ 1, 2 });
				saver.close(world);

				Assert::IsTrue(::io::Folder{ "worlds/" + world.getName() }.exists());
			}
		};
	}
}