#include "mesh.hpp"

#include "../gl_shared/common.hpp"
#include "scene.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

Mesh::Mesh(const MeshCreateInfo& info)
{
	glGenVertexArrays(1, &vao);
	SetTopology(info.topology);
	SetRender(info.render);
	SetTransparent(info.transparent);
	SetVertBuf(info.vertBuf);
	SetIndBuf(info.indBuf);
	SetColBuf(info.colBuf);
	SetUVBuf(info.uvBuf);
	SetDiffuse(info.diffuse);
	SetClipRect(info.hasClipRect, info.clipRect);
	SetModelMat4(info.model);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
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

void Mesh::SetVertBuf(SVertBuf object)
{
	using namespace GLShared;
	vertBuf = std::dynamic_pointer_cast<VertBuf>(object);
	if(vertBuf)
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vertBuf->bo);
		glVertexAttribPointer(ATTRIBUTE_VERTICES, 3, GL_FLOAT, GL_FALSE,
		                      0, nullptr);
		glEnableVertexAttribArray(ATTRIBUTE_VERTICES);
	}
	else
	{
		glBindVertexArray(vao);
		glDisableVertexAttribArray(ATTRIBUTE_VERTICES);
	}
}

void Mesh::SetIndBuf(SIndBuf object)
{
	using namespace GLShared;
	indBuf = std::dynamic_pointer_cast<IndBuf>(object);
	if(indBuf)
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuf->bo);
	}
	else
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0u);
	}
}

void Mesh::SetColBuf(SColBuf object)
{
	using namespace GLShared;
	colBuf = std::dynamic_pointer_cast<ColBuf>(object);
	if(colBuf)
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, colBuf->bo);
		glVertexAttribPointer(ATTRIBUTE_COLORS, 4, GL_FLOAT, GL_FALSE, 0,
		                      nullptr);
		glEnableVertexAttribArray(ATTRIBUTE_COLORS);
	}
	else
	{
		glBindVertexArray(vao);
		glDisableVertexAttribArray(ATTRIBUTE_COLORS);
	}
}

void Mesh::SetUVBuf(SUVBuf object)
{
	using namespace GLShared;
	uvBuf = std::dynamic_pointer_cast<UVBuf>(object);
	if(uvBuf)
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuf->bo);
		glVertexAttribPointer(ATTRIBUTE_UVS, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(ATTRIBUTE_UVS);
	}
	else
	{
		glBindVertexArray(vao);
		glDisableVertexAttribArray(ATTRIBUTE_UVS);
	}
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

} // namespace GLCore

} // namespace Detail

} // namespace Drawing
