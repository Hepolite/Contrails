
#pragma once

#include "io/File.h"

#include <allegro5/bitmap.h>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <string>
#include <unordered_map>

namespace render
{
	namespace allegro
	{
		class SpriteFrame
		{
		public:
			SpriteFrame() = delete;
			SpriteFrame(ALLEGRO_BITMAP * parent, const glm::ivec2 & pos, const glm::ivec2 & size) noexcept;
			SpriteFrame(const SpriteFrame &) noexcept = default;
			SpriteFrame(SpriteFrame && other) noexcept;
			~SpriteFrame() noexcept;

			SpriteFrame & operator=(const SpriteFrame &) noexcept = default;
			SpriteFrame & operator=(SpriteFrame && other) noexcept;

			void flip(bool horizontal, bool vertical);
			void tint(const glm::vec4 & color);

			inline auto getPos() const { return m_pos; }
			inline auto getSize() const { return m_size; }
			inline auto getTint() const { return glm::vec4{ m_tint.r, m_tint.g, m_tint.b, m_tint.a }; }
			inline auto getFlags() const { return m_flags; }

			void draw(const glm::vec2 & pos, float angle = 0.0f) const;
			void draw(const glm::vec2 & pos, const glm::vec2 & size, float angle = 0.0f) const;

			inline auto getHandle() const { return m_handle; }

		private:
			ALLEGRO_BITMAP * m_handle = nullptr;
			ALLEGRO_COLOR m_tint{ 1.0f, 1.0f, 1.0f, 1.0f };
			glm::ivec2 m_pos;
			glm::ivec2 m_size;
			int m_flags = 0;
		};

		class Sprite
		{
		public:
			Sprite() = default;
			Sprite(const Sprite &) = delete;
			Sprite(Sprite && other) noexcept;
			~Sprite();

			Sprite & operator=(const Sprite &) = delete;
			Sprite & operator=(Sprite && other) noexcept;

			bool create(unsigned int width, unsigned int height);
			bool load(const io::File & file);

			bool has(const std::string & name) const;
			bool add(const std::string & name, SpriteFrame && frame);
			const SpriteFrame & get(const std::string & name) const;

			inline auto getHandle() const { return m_handle; }

		private:
			ALLEGRO_BITMAP * m_handle = nullptr;

			std::unordered_map<std::string, SpriteFrame> m_frames;
		};
	}
}