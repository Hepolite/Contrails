
#include "CppUnitTest.h"

#include "logic/event/EventBus.h"
#include "world/io/WorldSaver.h"
#include "world/World.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace io
	{
		TEST_CLASS(WorldSaverTest)
		{
		public:
			WorldSaverTest() { init(); }
			~WorldSaverTest() { deinit(); }

			TEST_METHOD(WorldSaver_schedule)
			{
				WorldSaver saver{ m_folder };
				saver.schedule({ 3, 1, 4 });

				glm::ivec3 rpos;
				Assert::IsTrue(saver.extract(rpos));
				Assert::AreEqual({ 3, 1, 4 }, rpos);
				Assert::IsFalse(saver.extract(rpos));
			}

			TEST_METHOD(WorldSaver_writeMetadata)
			{
				WorldSaver saver{ m_folder };
				saver.inject(m_world);
				saver.writeMetadata();

				::io::File file{ m_folder.getPath() + "/header.xml" };
				Assert::IsTrue(file.exists());
			}
			TEST_METHOD(WorldSaver_writeBlockIds)
			{
				pugi::xml_document node;

				WorldSaver saver{ m_folder };
				saver.inject(m_world);
				saver.writeBlockIds(node);

				Assert::IsTrue(node.child("stone").attribute("id"));
				Assert::IsTrue(node.child("dirt").attribute("id"));
				Assert::IsTrue(node.child("grass").attribute("id"));
			}

			TEST_METHOD(WorldSaver_saveRegion)
			{
				m_world.write({ 1700, -200, 2500 }, data::BlockData{ 1, 2 });

				WorldSaver saver{ m_folder };
				saver.inject(m_world);
				saver.schedule({ 3, -1, 4 });
				saver.finish();

				Assert::IsTrue(::io::File{ m_folder.getPath() + "/3_-1_4.rvd" }.exists());
			}

		private:
			void init()
			{
				BlockRegistry registry;
				registry.add("stone");
				registry.add("dirt");
				registry.add("grass");

				m_world.inject(registry);
				m_world.inject(m_bus);
			}
			void deinit()
			{
				m_folder.erase(true);
			}

			::io::Folder m_folder{ "world_name" };
			logic::event::EventBus m_bus;
			World m_world;
		};
	}
}