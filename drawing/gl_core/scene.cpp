#include "scene.hpp"

#include "mesh.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

Scene* Scene::GetNext() const
{
	return next.get();
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
	viewProjChanged = true;
	return tmp;
}

} // namespace GLCore

} // namespace Detail

} // namespace Drawing
