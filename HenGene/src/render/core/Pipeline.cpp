
#include "Pipeline.h"

#include "render/opengl/OpenGL.h"

#include <allegro5/allegro.h>

void render::core::Pipeline::render(const Time & t, const Time & dt) const
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	al_flip_display();
}
