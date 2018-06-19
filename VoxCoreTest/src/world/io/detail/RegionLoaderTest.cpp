
#include "CppUnitTest.h"

#include "world/io/detail/RegionLoader.h"
#include "world/io/WorldSaver.h"
#include "world/World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace io
	{
		TEST_CLASS(RegionLoaderTest)
		{
		public:
			RegionLoaderTest() { init(); }
			~RegionLoaderTest() { deinit(); }

			TEST_METHOD(RegionLoader_read)
			{
				World world;
				RegionLoader loader{ "world" };
				loader.read(world, { 0, 0, 0 });
				loader.read(world, { 3, -1, 4 });

				Assert::AreEqual(1u, world.readBlock({ 50, 80, 120 }).getId());
				Assert::AreEqual(2u, world.readBlock({ 50, 80, 120 }).getLight());
				Assert::AreEqual(1u, world.readBlock({ 1700, -200, 2500 }).getId());
				Assert::AreEqual(2u, world.readBlock({ 1700, -200, 2500 }).getLight());
			}

		private:
			void init()
			{
				World world;
				world.write({ 50, 80, 120 }, data::BlockData{ 1, 2 });
				world.write({ 1700, -200, 2500 }, data::BlockData{ 1, 2 });

				WorldSaver saver{ "world" };
				saver.inject(world);
				saver.schedule({ 0, 0, 0 });
				saver.schedule({ 3, -1, 4 });
				saver.finish();
			}
			void deinit()
			{
				::io::Folder{ "world" }.erase(true);
			}
		};
	}
}