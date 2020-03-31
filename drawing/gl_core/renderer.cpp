#include "renderer.hpp"

#include <exception>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr, glm::identity

#include "mesh.hpp"
#include "scene2d.hpp"
#include "scene3d.hpp"
#include "../gl_shared/gl_include.hpp"
#include "../gl_shared/shader.hpp"
#include "../gl_shared/program.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

Renderer::Renderer(SDL_Window* sdlWindow) : GLShared::Renderer(sdlWindow)
{
	using namespace GLShared;
	// Set up framebuffer blit stuff
	const auto& prog = programs[PROGRAM_TEXTURE_PLUS_COLOR];
	spo = prog.spo;
	mvpUniLoc = prog.GetUniformLocation(UNIFORM_MVP_MAT);
	// Set up Vertex Array Object
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, quad.vb->bo);
	glVertexAttribPointer(ATTRIBUTE_VERTICES, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(ATTRIBUTE_VERTICES);
	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad.ib->bo);
	// UV buffer
	glBindBuffer(GL_ARRAY_BUFFER, quad.ub->bo);
	glVertexAttribPointer(ATTRIBUTE_UVS, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(ATTRIBUTE_UVS);
}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &vao);
}

SScene Renderer::NewScene2D(const SceneCreateInfo& info)
{
	return std::make_shared<Scene2D>(*this, info);
}

SScene Renderer::NewScene3D(const SceneCreateInfo& info)
{
	return std::make_shared<Scene3D>(*this, info);
}

SMesh Renderer::NewMesh(const MeshCreateInfo& info)
{
	return std::make_shared<Mesh>(info);
}

void Renderer::BlitToWindowFramebuffer(const GLShared::Rect& viewport, GLuint to)
{
	using namespace GLShared;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_SCISSOR_TEST);
	glViewport(viewport.x, viewport.y, viewport.w, viewport.h);
	glUseProgram(spo);
	glUniformMatrix4fv(mvpUniLoc, 1, GL_FALSE, glm::value_ptr(glm::identity<glm::mat4>()));
	glBindTexture(GL_TEXTURE_2D, to);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, nullptr);
}

} // GLCore

} // Detail

} // Drawing
