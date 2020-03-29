#include "scene.hpp"

#include "mesh.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

// protected

void Scene::CalculateMVP(Mesh& mesh) const
{
	mesh.mvp = ViewProjection() * mesh.model;
}

} // namespace GLCore

} // namespace Detail

} // namespace Drawing
