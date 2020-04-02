#include "mesh.hpp"

#include "common.hpp"
#include "mesh_listener.hpp"
#include "scene.hpp"

namespace Ego
{

namespace GLShared
{

Mesh::Mesh(const MeshCreateInfo& info) :
	listener(nullptr)
{
	SetTopology(info.topology);
	SetRender(info.render);
	SetTransparent(info.transparent);
	SetDiffuse(info.diffuse);
	SetClipRect(info.clipRect);
	SetModelMat4(info.model);
}

void Mesh::SetTopology(MeshTopology value)
{
	topology = GLShared::GLTopologyFromEnum(value);
}

void Mesh::SetRender(bool value)
{
	render = value;
}

void Mesh::SetTransparent(bool value)
{
	transparent = value;
	if(listener)
		listener->OnMeshTransparencyChange(*this);
}

void Mesh::SetDiffuse(const SCTexture& object)
{
	using namespace GLShared;
	diffuse = std::dynamic_pointer_cast<const Texture>(object);
}

void Mesh::SetClipRect(const glm::ivec4* rect)
{
	if((hasScissor = rect != nullptr))
		sci = *rect;
}

void Mesh::SetModelMat4(const glm::mat4& mat)
{
	model = mat;
	if(listener)
		listener->OnMeshModelMatChange(*this);
}

glm::mat4 Mesh::GetModelMat4() const
{
	return model;
}

} // namespace GLShared

} // namespace Ego
