#include "mesh.hpp"

#include "common.hpp"
#include "scene.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

Mesh::Mesh(const MeshCreateInfo& info) :
	scene(nullptr)
{
	SetTopology(info.topology);
	SetRender(info.render);
	SetTransparent(info.transparent);
	SetDiffuse(info.diffuse);
	SetClipRect(info.hasClipRect, info.clipRect);
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
	if(scene)
		scene->OnMeshTransparencyChange(*this);
}

void Mesh::SetDiffuse(STexture object)
{
	using namespace GLShared;
	diffuse = std::dynamic_pointer_cast<Texture>(object);
}

void Mesh::SetClipRect(bool has, const glm::vec4& rect)
{
	hasScissor = has;
	if(hasScissor)
		sci = GLShared::RectFromVec4(rect);
}

void Mesh::SetModelMat4(const glm::mat4& mat)
{
	model = mat;
	if(scene)
		scene->OnMeshModelMatChange(*this);
}

glm::mat4 Mesh::GetModelMat4() const
{
	return model;
}

} // namespace GLShared

} // namespace Detail

} // namespace Drawing
