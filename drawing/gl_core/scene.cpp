#include "scene.hpp"

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

void Scene::SetNext(Drawing::Scene scene)
{
	next = std::dynamic_pointer_cast<Scene>(scene);
}

} // namespace GLCore

} // namespace Detail

} // namespace Drawing
