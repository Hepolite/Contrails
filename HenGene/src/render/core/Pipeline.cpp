
#include "Pipeline.h"

#include "render/opengl/OpenGL.h"

#include <allegro5/allegro.h>

void render::core::Pipeline::render(const Time & t, const Time & dt, float pt) const
{
	glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (m_scene != nullptr)
		m_scene->render(t, dt, pt);
	if (m_gui != nullptr)
	{
		int boundProgram, boundVao, boundVbo;
		glGetIntegerv(GL_CURRENT_PROGRAM, &boundProgram);
		glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &boundVao);
		glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &boundVbo);

		glUseProgram(0);
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		m_gui->render();

		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glUseProgram(boundProgram);
		glBindVertexArray(boundVao);
		glBindBuffer(GL_ARRAY_BUFFER, boundVbo);
	}

	al_flip_display();
}
