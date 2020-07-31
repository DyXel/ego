#include "renderer.hpp"

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr, glm::identity

#include "mesh.hpp"
#include "scene2d.hpp"
#include "scene3d.hpp"
#include "../gl_shared/gl_include.hpp"

namespace Ego::GLES
{

Renderer::Renderer() :
	GLShared::Renderer(),
	prog(programs[GLShared::PROGRAM_TEXTURE_PLUS_COLOR]),
	mvpUniLoc(prog.GetUniformLocation(GLShared::UNIFORM_MVP_MAT)),
	im(glm::identity<glm::mat4>())
{}

SScene Renderer::NewScene2D(const SceneCreateInfo& info)
{
	return std::make_shared<Scene2D>(cache, *this, info);
}

SScene Renderer::NewScene3D(const SceneCreateInfo& info)
{
	return std::make_shared<Scene3D>(cache, *this, info);
}

SMesh Renderer::NewMesh(const MeshCreateInfo& info)
{
	return std::make_shared<Mesh>(info);
}

void Renderer::BlitToWindowFramebuffer(const GLShared::Scene& scene)
{
	cache.SetDepthTest(false);
	cache.SetCullFace(false);
	cache.SetScissorTest(false);
	const auto& vp = scene.Viewport();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(vp.x, vp.y, vp.z, vp.w);
	glUseProgram(prog.spo);
	glUniformMatrix4fv(mvpUniLoc, 1, GL_FALSE, glm::value_ptr(im));
	glBindTexture(GL_TEXTURE_2D, scene.TextureObject());
	//
	glBindBuffer(GL_ARRAY_BUFFER, quad.vb->bo);
	glVertexAttribPointer(GLShared::ATTRIBUTE_VERTICES, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
	//
	glBindBuffer(GL_ARRAY_BUFFER, quad.ub->bo);
	glVertexAttribPointer(GLShared::ATTRIBUTE_UVS, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(GLShared::ATTRIBUTE_UVS);
	//
	glDisableVertexAttribArray(GLShared::ATTRIBUTE_COLORS);
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad.ib->bo);
	glDrawElements(GL_TRIANGLE_STRIP, quad.ib->count, GL_UNSIGNED_SHORT, nullptr);
}

} // namespace Ego::GLES
