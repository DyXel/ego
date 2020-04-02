#include "mesh.hpp"

#include "../gl_shared/common.hpp"

namespace Ego
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

void Mesh::SetVertBuf(const SCVertBuf& object)
{
	using namespace GLShared;
	vertBuf = std::dynamic_pointer_cast<const VertBuf>(object);
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

void Mesh::SetIndBuf(const SCIndBuf& object)
{
	using namespace GLShared;
	indBuf = std::dynamic_pointer_cast<const IndBuf>(object);
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

void Mesh::SetColBuf(const SCColBuf& object)
{
	using namespace GLShared;
	colBuf = std::dynamic_pointer_cast<const ColBuf>(object);
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

void Mesh::SetUVBuf(const SCUVBuf& object)
{
	using namespace GLShared;
	uvBuf = std::dynamic_pointer_cast<const UVBuf>(object);
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

} // namespace Ego
