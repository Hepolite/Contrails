
#include "CppUnitTest.h"

#include "world/io/WorldLoader.h"
#include "world/io/WorldSaver.h"
#include "world/World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace io
	{
		TEST_CLASS(WorldLoaderTest)
		{
		public:
			WorldLoaderTest() { init(); }
			~WorldLoaderTest() { deinit(); }

			TEST_METHOD(WorldLoader_readMetadata)
			{
				World world;

				WorldLoader loader{ "world" };
				loader.inject(world);
				loader.readMetadata();

				validateBlockIds(world);
			}
			TEST_METHOD(WorldLoader_readBlockIds)
			{
				World world;
				pugi::xml_document doc;
				doc.load_file("world/header.xml");

				WorldLoader loader{ "world" };
				loader.inject(world);
				loader.readBlockIds(doc.child("blocks"));

				validateBlockIds(world);
			}

			TEST_METHOD(WorldLoader_readWorld)
			{
				World world;

				WorldLoader loader{ "world" };
				loader.inject(world);
				loader.readWorld();
				loader.finish();

				Assert::AreEqual(1u, world.readBlock({ 50, 80, 120 }).getId());
				Assert::AreEqual(2u, world.readBlock({ 50, 80, 120 }).getLight());
				Assert::AreEqual(1u, world.readBlock({ 1700, -200, 2500 }).getId());
				Assert::AreEqual(2u, world.readBlock({ 1700, -200, 2500 }).getLight());
			}

		private:
			void init()
			{
				BlockRegistry registry;
				registry.add("stone");
				registry.add("grass");

				World world;
				world.inject(registry);
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
		
			void validateBlockIds(const World & world)
			{
				Assert::AreEqual(0u, world.getBlockRegistry()["air"].m_id);
				Assert::AreEqual(1u, world.getBlockRegistry()["stone"].m_id);
				Assert::AreEqual(2u, world.getBlockRegistry()["grass"].m_id);
			}
		};
	}
}