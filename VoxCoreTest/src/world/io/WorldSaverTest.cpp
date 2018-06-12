
#include "CppUnitTest.h"

#include "logic/event/EventBus.h"
#include "world/io/WorldSaver.h"
#include "world/World.h"

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

			TEST_METHOD(WorldSaver_writeMetadata)
			{
				WorldSaver saver{ m_folder };
				saver.inject(m_world);
				saver.writeMetadata();

				Assert::IsTrue(::io::File{ m_folder.getPath() + "/header.xml" }.exists());
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

		private:
			void init()
			{
				BlockRegistry registry;
				registry.add("stone");
				registry.add("dirt");
				registry.add("grass");
				m_world.inject(registry);
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