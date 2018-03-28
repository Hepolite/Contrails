
#pragma once

#include <stdint.h>

namespace world
{
	namespace render
	{
		namespace data
		{
			class TextureData
			{
			public:
				TextureData() noexcept = default;
				TextureData(uint32_t data) noexcept : m_data(data) {}
				TextureData(const TextureData &) noexcept = default;
				TextureData(TextureData &&) noexcept = default;
				~TextureData() = default;

				TextureData & operator=(const TextureData &) noexcept = default;
				TextureData & operator=(TextureData &&) noexcept = default;

				inline auto getData() const { return m_data; }

			private:
				uint32_t m_data;
			};
		}
	}
}