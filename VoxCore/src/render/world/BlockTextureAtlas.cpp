
#include "BlockTextureAtlas.h"

#include "render/opengl/OpenGL.h"

#include <allegro5/allegro.h>

unsigned int render::world::BlockTextureAtlas::attach(const io::File & file)
{
	if (m_built || !file.exists())
		return 0u;

	const auto path = file.getPath();
	const auto it = m_files.find(path);
	if (it != m_files.end())
		return it->second;

	const auto index = attach(al_load_bitmap(path.c_str()), true);
	m_files.emplace(path, index);
	return index;
}
unsigned int render::world::BlockTextureAtlas::attach(ALLEGRO_BITMAP * bitmap)
{
	return attach(bitmap, false);
}
unsigned int render::world::BlockTextureAtlas::attach(ALLEGRO_BITMAP * bitmap, bool owned)
{
	if (m_built || bitmap == nullptr)
		return 0u;

	unsigned int index = m_bitmaps.size();

	int width = al_get_bitmap_width(bitmap);
	int height = al_get_bitmap_height(bitmap);
	if (m_width == 0u || m_height == 0u)
	{
		m_width = width;
		m_height = height;
	}

	if (width != m_width || height != m_height)
	{
		for (int y = 0; y < height; y += m_height)
		for (int x = 0; x < width; x += m_width)
		{
			auto subBitmap = al_create_sub_bitmap(bitmap, x, y, m_width, m_height);
			m_ownedBitmaps.push_back(subBitmap);
			m_bitmaps.push_back(subBitmap);
		}
	}
	else
		m_bitmaps.push_back(bitmap);

	if (owned)
		m_ownedBitmaps.push_back(bitmap);
	return index;
}

bool render::world::BlockTextureAtlas::build()
{
	if (m_built || m_bitmaps.empty())
		return false;
	m_built = true;
	bind();

	glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, m_width, m_height, m_bitmaps.size(), 0, GL_RGBA, GL_UNSIGNED_INT, (void*)0);
	unsigned int index = 0;
	for (auto bitmap : m_bitmaps)
	{
		// Dark sorcery. Don't question it. This copies the Allegro bitmap data into the OpenGL texture
		ALLEGRO_LOCKED_REGION *region = al_lock_bitmap(bitmap, al_get_bitmap_format(bitmap), ALLEGRO_LOCK_READONLY);
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, index++, m_width, m_height, 1, GL_BGRA, GL_UNSIGNED_BYTE, (uint8_t*)region->data + (m_height - 1) * region->pitch);
		al_unlock_bitmap(bitmap);
	}

	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

	cleanup();
	return true;
}

void render::world::BlockTextureAtlas::cleanup()
{
	for (auto bitmap : m_ownedBitmaps)
		al_destroy_bitmap(bitmap);
	m_ownedBitmaps.clear();
	m_bitmaps.clear();
	m_files.clear();
}
