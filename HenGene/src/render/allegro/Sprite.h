
#pragma once

#include "io/File.h"

#include <allegro5/bitmap.h>

namespace render
{
	namespace allegro
	{
		class Sprite
		{
		public:
			Sprite() noexcept = default;
			Sprite(const Sprite &) = delete;
			Sprite(Sprite && other) noexcept;
			~Sprite();

			Sprite & operator=(const Sprite &) = delete;
			Sprite & operator=(Sprite && other) noexcept;

			void create(unsigned int width, unsigned int height);
			void load(const io::File & file);
			void release();

			inline auto getHandle() const { return m_handle; }

		private:
			ALLEGRO_BITMAP * m_handle = nullptr;
		};
	}
}