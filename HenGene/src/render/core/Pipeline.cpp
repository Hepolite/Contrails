
#include "Pipeline.h"

#include "render/opengl/OpenGL.h"

#include <allegro5/allegro.h>

void render::core::Pipeline::render(const Time & t, const Time & dt) const
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_scene != nullptr)
		m_scene->render(t, dt);

	if (m_gui != nullptr)
	{
		//m_gui->renderOpenGLContext
		glUseProgram(0);
		glBindVertexArray(0);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		//m_gui->renderAllegroContext
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
	}

	al_flip_display();
}
