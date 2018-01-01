
#include "Side.h"

const world::util::Side & world::util::fromName(const std::string & name)
{
	if (name == "front")
		return SIDE_FRONT;
	if (name == "left")
		return SIDE_LEFT;
	if (name == "back")
		return SIDE_BACK;
	if (name == "right")
		return SIDE_RIGHT;
	if (name == "top")
		return SIDE_TOP;
	if (name == "bottom")
		return SIDE_BOTTOM;
	return SIDE_UNKNOWN;
}
std::vector<world::util::Side> world::util::fromNameExt(const std::string & name)
{
	if (name == "all")
		return { SIDE_FRONT, SIDE_LEFT, SIDE_BACK, SIDE_RIGHT, SIDE_TOP, SIDE_BOTTOM, SIDE_UNKNOWN };
	if (name == "side")
		return { SIDE_FRONT, SIDE_LEFT, SIDE_BACK, SIDE_RIGHT };
	return { fromName(name) };
}
