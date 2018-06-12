
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
			RegionSaverTest() { m_folder.create(); }
			~RegionSaverTest() { m_folder.erase(true); }

			TEST_METHOD(RegionSaver_write)
			{
				World world;
				world.write({ 400, 50, 50 }, data::BlockData{ 1, 2 });

				RegionSaver saver{ m_folder };
				saver.write(world, { 0, 0, 0 });

				Assert::IsTrue(::io::File{ m_folder.getPath() + "/0_0_0.rvd" }.exists());
			}

		private:
			::io::Folder m_folder{ "world_name" };
		};
	}
}