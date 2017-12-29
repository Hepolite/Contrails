
#pragma once

#define ALLEGRO_UNSTABLE

#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>
#include <gl/GL.h>

namespace render
{
	namespace opengl
	{
		bool hasOpenGLError(const char * function, unsigned int line);
	}
}

#define HAS_GL_ERROR hasOpenGLError(__func__, __LINE__);