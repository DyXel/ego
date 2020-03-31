#include "scene.hpp"

#include "mesh.hpp"

namespace Drawing
{

namespace GLShared
{

Scene::Scene(IProgramProvider& pp, const SceneCreateInfo& info) :
	pp(pp),
	clearBits(GLClearBitsFromScenePropertyBits(info.properties)),
	backfaceCull(info.properties & SCENE_PROPERTY_BACKFACE_CULLING_BIT),
	depthTest(info.properties & SCENE_PROPERTY_ENABLE_DEPTH_TEST_BIT),
	clearColor(info.clearColor)
{
	// NOTE: We set initial sizes to 1, because OpenGL errors out if they are 0.
	constexpr int NOT0 = 1;
	glGenFramebuffers(1, &fbo);
	glGenTextures(1, &to);
	glGenRenderbuffers(1, &rbo);
	// Set up texture (color buffer)
	glBindTexture(GL_TEXTURE_2D, to);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, NOT0, NOT0, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	// Set up renderbuffer (depth buffer)
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, NOT0, NOT0);
	// Finally, setup framebuffer by attaching everything to it
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, to, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
	// NOTE: for GLES, RGBA4 should be used as format, information:
	// https://www.khronos.org/registry/OpenGL/specs/es/2.0/es_cm_spec_2.0.pdf
	// 4.4.5 Framebuffer Completeness
	SetViewProjectionMat4(info.viewProj);
	SetViewport(info.viewport);
	SetNext(info.next);
}

Scene::~Scene()
{
	glDeleteRenderbuffers(1, &rbo);
	glDeleteTextures(1, &to);
	glDeleteFramebuffers(1, &fbo);
}

void Scene::Draw()
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glViewport(0, 0, vp.w, vp.h);
	if(clearBits)
	{
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
		glClear(clearBits);
	}
	if(backfaceCull)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
	if(depthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

Scene* Scene::Next() const
{
	return next.get();
}

GLuint Scene::TextureObject() const
{
	return to;
}

const GLShared::Rect& Scene::Viewport() const
{
	return vp;
}

void Scene::SetViewport(const glm::vec4& rect)
{
	vp = GLShared::RectFromVec4(rect);
	glBindTexture(GL_TEXTURE_2D, to);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp.w, vp.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, vp.w, vp.h);
}

void Scene::SetNext(SScene scene)
{
	next = std::dynamic_pointer_cast<Scene>(scene);
}

void Scene::SetViewProjectionMat4(const glm::mat4& mat)
{
	viewProj = mat;
	viewProjChanged = true;
}

// protected

const glm::mat4& Scene::ViewProjection() const
{
	return viewProj;
}

void Scene::CalculateMVP(Mesh& mesh) const
{
	mesh.mvp = viewProj * mesh.model;
}

bool Scene::WasViewProjectionSet() const
{
	return viewProjChanged;
}

bool Scene::WasViewProjectionSet([[maybe_unused]] bool ignored)
{
	bool tmp = viewProjChanged;
	viewProjChanged = false;
	return tmp;
}

void Scene::UseMeshProgram(const Mesh& mesh)
{
	bool textured;
	if((textured = !!mesh.diffuse))
		glUseProgram(pp.GetProgram(PROGRAM_TEXTURE_PLUS_COLOR).spo);
	else
		glUseProgram(pp.GetProgram(PROGRAM_ONLY_COLOR).spo);
	if(textured)
		glBindTexture(GL_TEXTURE_2D, mesh.diffuse->to);
}

void Scene::UseMeshScissor(const Mesh& mesh)
{
	if(mesh.hasScissor)
	{
		glEnable(GL_SCISSOR_TEST);
		glScissor(mesh.sci.x, mesh.sci.y, mesh.sci.w, mesh.sci.h);
	}
	else
	{
		glDisable(GL_SCISSOR_TEST);
	}
}

} // namespace GLShared

} // namespace Drawing
