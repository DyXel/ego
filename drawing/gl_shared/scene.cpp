#include "scene.hpp"

#include "mesh.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

Scene::Scene(IProgramProvider& pp, const SceneCreateInfo& info) :
	pp(pp)
{
	SetViewProjectionMat4(info.viewProj);
	SetViewport(info.viewport);
	SetNext(info.next);
}

void Scene::SetViewport(const glm::vec4& rect)
{
	viewport = GLShared::RectFromVec4(rect);
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

Scene* Scene::GetNext() const
{
	return next.get();
}

// protected

void Scene::ApplyViewport() const
{
	glViewport(viewport.x, viewport.y, viewport.w, viewport.h);
}

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
	GLuint programToUse;
	if((textured = !!mesh.diffuse))
		programToUse = pp.GetProgram(PROGRAM_TEXTURE_PLUS_COLOR).spo;
	else
		programToUse = pp.GetProgram(PROGRAM_ONLY_COLOR).spo;
	if(programToUse != cache.lastProgram)
		glUseProgram(cache.lastProgram = programToUse);
	if(textured)
		glBindTexture(GL_TEXTURE_2D, mesh.diffuse->to);
}

void Scene::UseMeshScissor(const Mesh& mesh)
{
	if(mesh.hasScissor)
	{
		if(!cache.usingScissor)
		{
			cache.usingScissor = true;
			glEnable(GL_SCISSOR_TEST);
		}
		glScissor(mesh.sci.x, mesh.sci.y, mesh.sci.w, mesh.sci.h);
	}
	else if(cache.usingScissor)
	{
		cache.usingScissor = false;
		glDisable(GL_SCISSOR_TEST);
	}
}

} // namespace GLShared

} // namespace Detail

} // namespace Drawing
