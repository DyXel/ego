#include "scene.hpp"

#include "cache.hpp"
#include "mesh.hpp"

namespace Ego
{

namespace GLShared
{

Scene::Scene(Cache& cache, IProgramProvider& pp, const SceneCreateInfo& info) :
	cache(cache),
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
	glViewport(0, 0, vp.z, vp.w);
	if(clearBits)
	{
		glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
		glClear(clearBits);
	}
	cache.SetCullFace(backfaceCull);
	cache.SetDepthTest(depthTest);
}

Scene* Scene::Next() const
{
	return next.get();
}

GLuint Scene::FramebufferObject() const
{
	return fbo;
}

GLuint Scene::TextureObject() const
{
	return to;
}

const glm::ivec4& Scene::Viewport() const
{
	return vp;
}

void Scene::SetViewport(const glm::ivec4& rect)
{
	vp = rect;
	glBindTexture(GL_TEXTURE_2D, to);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp.z, vp.w, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, vp.z, vp.w);
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
		cache.UseProgram(pp.GetProgram(PROGRAM_TEXTURE_PLUS_COLOR).spo);
	else
		cache.UseProgram(pp.GetProgram(PROGRAM_ONLY_COLOR).spo);
	if(textured)
		glBindTexture(GL_TEXTURE_2D, mesh.diffuse->to);
}

void Scene::UseMeshScissor(const Mesh& mesh)
{
	cache.SetScissorTest(mesh.hasScissor);
	if(mesh.hasScissor)
		glScissor(mesh.sci.x, mesh.sci.y, mesh.sci.z, mesh.sci.w);
}

} // namespace GLShared

} // namespace Ego
