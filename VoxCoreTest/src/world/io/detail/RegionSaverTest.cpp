
#include "CppUnitTest.h"

#include "io/File.h"
#include "io/Folder.h"
#include "world/io/detail/RegionSaver.h"
#include "world/World.h"

#include <glm/vec3.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace io
	{
		TEST_CLASS(RegionSaverTest)
		{
		public:
			~RegionSaverTest() { m_folder.erase(true); }

			TEST_METHOD(RegionSaver_write)
			{
				World world;
				world.write({ 50, 80, 120 }, data::BlockData{ 1, 2 });
				world.write({ 1700, -200, 2500 }, data::BlockData{ 1, 2 });

				RegionSaver saver{ m_folder };
				saver.write(world, { 0, 0, 0 });
				saver.write(world, { 3, -1, 4 });

				Assert::IsTrue(::io::File{ m_folder.getPath() + "/0_0_0.rvd" }.exists());
				Assert::IsTrue(::io::File{ m_folder.getPath() + "/3_-1_4.rvd" }.exists());
			}

		private:
			::io::Folder m_folder{ "world_name" };
		};
	}
}