#include "mesh.hpp"

#include "../gl_shared/common.hpp"

namespace Drawing
{

namespace GLCore
{

Mesh::Mesh(const MeshCreateInfo& info) : GLShared::Mesh(info)
{
	glGenVertexArrays(1, &vao);
	SetVertBuf(info.vertBuf);
	SetIndBuf(info.indBuf);
	SetColBuf(info.colBuf);
	SetUVBuf(info.uvBuf);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
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

} // namespace GLCore

} // namespace Drawing
