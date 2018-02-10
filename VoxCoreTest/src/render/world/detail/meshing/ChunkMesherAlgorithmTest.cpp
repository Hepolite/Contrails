
#include "CppUnitTest.h"

#include "render/world/detail/meshing/NaiveGreedyMesher.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace world
	{
		TEST_CLASS(NaiveGreedyMesherTest)
		{
		public:
			NaiveGreedyMesherTest() { initialize(); }

			TEST_METHOD(LayerData_set)
			{
				BlockData block{ 2000u, 17u };
				ColorData color{ { 7u, 31u, 13u } };
				TextureData texture{};
				LayerData data;

				data.set(block, color, texture);
				Assert::AreEqual(block.getId(), data.getBlock().getId());
				Assert::AreEqual(block.getLight(), data.getBlock().getLight());
				Assert::AreEqual(color.getColor(), data.getColor().getColor());
				Assert::AreEqual(texture.getData(), data.getTexture().getData());
			}
			TEST_METHOD(LayerData_empty)
			{
				LayerData dataA, dataB;
				dataA.set({ 42u, 1u }, { { 0u, 0u, 0u } }, {});

				Assert::IsFalse(dataA.empty());
				Assert::IsTrue(dataB.empty());
			}

			TEST_METHOD(LayerMask_put)
			{
				LayerData data;
				data.set({ 21u, 31u }, { { 1u, 2u, 3u } }, {});
				LayerMask mask;
				mask.put({ 20u, 12u }, data);

				const auto result = mask.get({ 20u, 12u });
				Assert::AreEqual(21u, result.getBlock().getId());
				Assert::AreEqual(31u, result.getBlock().getLight());
				Assert::AreEqual({ 1u, 2u, 3u }, data.getColor().getColor());
				Assert::AreEqual(0u, data.getTexture().getData());
			}
			TEST_METHOD(LayerMask_extract)
			{
				LayerData dataA, dataB;
				dataA.set({ 21u, 31u }, { { 1u, 2u, 3u } }, {});
				dataB.set({ 21u, 30u }, { { 1u, 2u, 3u } }, {});
				LayerMask mask;
				mask.put({ 0u, 0u }, dataA);
				mask.put({ 1u, 0u }, dataA);
				mask.put({ 2u, 0u }, dataB);
				mask.put({ 2u, 1u }, dataB);
				MeshFace face;

				Assert::IsTrue(mask.extract(face));
				Assert::AreEqual({ 2u, 1u }, face.m_size);
				Assert::AreEqual(dataA.getBlock().getId(), face.m_block.getId());
				Assert::AreEqual(dataA.getBlock().getLight(), face.m_block.getLight());
				Assert::AreEqual(dataA.getColor().getColor(), face.m_color.getColor());
				Assert::AreEqual(dataA.getTexture().getData(), face.m_texture.getData());

				Assert::IsTrue(mask.extract(face));
				Assert::AreEqual({ 1u, 2u }, face.m_size);
				Assert::AreEqual(dataB.getBlock().getId(), face.m_block.getId());
				Assert::AreEqual(dataB.getBlock().getLight(), face.m_block.getLight());
				Assert::AreEqual(dataB.getColor().getColor(), face.m_color.getColor());
				Assert::AreEqual(dataB.getTexture().getData(), face.m_texture.getData());

				Assert::IsFalse(mask.extract(face));
			}
		
			TEST_METHOD(NaiveGreedyMesher_getLayerData)
			{
				const auto dataA = m_mesher.getLayerData({ 3u, 1u, 1u }, ::world::util::SIDE_TOP);
				const auto dataB = m_mesher.getLayerData({ 4u, 1u, 1u }, ::world::util::SIDE_TOP);

				Assert::AreEqual(1u, dataA.getBlock().getId());
				Assert::AreEqual(31u, dataA.getBlock().getLight());
				Assert::AreEqual({ 1u, 2u, 3u }, dataA.getColor().getColor());
				Assert::IsTrue(dataB.empty());
			}
			TEST_METHOD(NaiveGreedyMesher_getLayerMask)
			{
				auto maskA = m_mesher.getLayerMask(1u, ::world::util::SIDE_TOP);
				auto maskB = m_mesher.getLayerMask(1u, ::world::util::SIDE_RIGHT);
				MeshFace face;

				Assert::IsTrue(maskA.extract(face));
				Assert::AreEqual({ 3u, 1u }, face.m_pos);
				Assert::AreEqual({ 1u, 1u }, face.m_size);
				Assert::AreEqual(1u, face.m_block.getId());
				Assert::AreEqual(31u, face.m_block.getLight());
				Assert::AreEqual({ 1u, 2u, 3u }, face.m_color.getColor());

				Assert::IsFalse(maskA.extract(face));


				Assert::IsTrue(maskB.extract(face));
				Assert::AreEqual({ 3u, 1u }, face.m_pos);
				Assert::AreEqual({ 1u, 1u }, face.m_size);
				Assert::AreEqual(1u, face.m_block.getId());
				Assert::AreEqual(25u, face.m_block.getLight());
				Assert::AreEqual({ 5u, 6u, 7u }, face.m_color.getColor());

				Assert::IsTrue(maskB.extract(face));
				Assert::AreEqual({ 4u, 1u }, face.m_pos);
				Assert::AreEqual({ 1u, 2u }, face.m_size);
				Assert::AreEqual(1u, face.m_block.getId());
				Assert::AreEqual(31u, face.m_block.getLight());
				Assert::AreEqual({ 1u, 2u, 3u }, face.m_color.getColor());

				Assert::IsFalse(maskB.extract(face));
			}

		private:
			void initialize()
			{
				m_mesher.inject(m_registry);
				m_mesher.inject(m_region);
				m_mesher.inject(m_mesh);

				m_registry[1u].m_texture->m_lookup = [](auto &, auto &, auto &) { return 0u; };

				m_region.write({ 3u, 0u, 1u }, BlockData{ 0u, 25u }, ColorData{ { 5u, 6u, 7u } });
				m_region.write({ 4u, 0u, 1u }, BlockData{ 0u, 31u }, ColorData{ { 1u, 2u, 3u } });
				m_region.write({ 4u, 0u, 2u }, BlockData{ 0u, 31u }, ColorData{ { 1u, 2u, 3u } });

				m_region.write({ 3u, 1u, 1u }, BlockData{ 1u, 0u });
				m_region.write({ 3u, 1u, 2u }, BlockData{ 0u, 31u }, ColorData{ { 1u, 2u, 3u } });
				m_region.write({ 4u, 1u, 1u }, BlockData{ 1u, 0u });
				m_region.write({ 4u, 1u, 2u }, BlockData{ 1u, 0u });
			}

			setup::Context m_context;
			BlockRenderRegistry m_registry;
			BlockRegion m_region;
			ChunkMesh m_mesh;
			NaiveGreedyMesher m_mesher;
		};
	}
}