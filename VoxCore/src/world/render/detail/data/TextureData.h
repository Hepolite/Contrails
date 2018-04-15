
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
				TextureData(unsigned int texture, unsigned int meta, unsigned int hash) noexcept;
				TextureData(const TextureData &) noexcept = default;
				TextureData(TextureData &&) noexcept = default;
				~TextureData() = default;

				TextureData & operator=(const TextureData &) noexcept = default;
				TextureData & operator=(TextureData &&) noexcept = default;

				void setTexture(unsigned int texture);
				void setMeta(unsigned int meta);
				void setHash(unsigned int meta);
				unsigned int getTexture() const;
				unsigned int getMeta() const;
				unsigned int getHash() const;

				inline auto getData() const { return m_data; }

			private:
				uint32_t m_data = 0u;
			};
		}
	}
}