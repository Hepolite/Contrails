
#include "FactorySprite.h"

#include <pugixml/pugixml.hpp>

void asset::util::LoaderSprite::load(render::allegro::Sprite & asset, const io::File & file) const
{
}

void asset::util::BuilderSprite::build(render::allegro::Sprite & asset, unsigned int width, unsigned int height) const
{
	asset.create(width, height);
}
