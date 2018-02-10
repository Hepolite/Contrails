
#pragma once

#include <glm/vec3.hpp>
#include <stdint.h>

namespace world
{
	namespace data
	{
		class BlockData
		{
		public:
			BlockData() noexcept = default;
			BlockData(uint16_t data) noexcept : m_data(data) {}
			BlockData(unsigned int id, unsigned int light) noexcept;
			BlockData(const BlockData &) noexcept = default;
			BlockData(BlockData &&) noexcept = default;
			~BlockData() = default;

			BlockData & operator=(const BlockData &) noexcept = default;
			BlockData & operator=(BlockData &&) noexcept = default;

			void setId(unsigned int id);
			void setLight(unsigned int light);
			unsigned int getId() const;
			unsigned int getLight() const;

			inline auto getData() const { return m_data; }

		private:
			uint16_t m_data = 0u;
		};
		
		class ColorData
		{
		public:
			ColorData() noexcept = default;
			ColorData(uint16_t data) noexcept : m_data(data) {}
			ColorData(const glm::uvec3 & color) noexcept;
			ColorData(const ColorData &) noexcept = default;
			ColorData(ColorData &&) noexcept = default;
			~ColorData() = default;

			ColorData & operator=(const ColorData &) noexcept = default;
			ColorData & operator=(ColorData &&) noexcept = default;

			void setColor(const glm::uvec3 & color);
			glm::uvec3 getColor() const;

			inline auto getData() const { return m_data; }

		private:
			uint16_t m_data = 0u;
		};
	}
}