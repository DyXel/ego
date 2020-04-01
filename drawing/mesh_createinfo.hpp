#ifndef DRAWING_MESH_CREATEINFO_HPP
#define DRAWING_MESH_CREATEINFO_HPP
#include <glm/mat4x4.hpp>
#include <glm/ext/vector_int4.hpp>

#include "drawing.hpp"
#include "enums.hpp"

namespace Drawing
{

struct MeshCreateInfo
{
	MeshTopology topology;
	bool render;
	bool transparent;
	SCVertBuf vertBuf;
	SCIndBuf indBuf;
	SCColBuf colBuf;
	SCUVBuf uvBuf;
	SCTexture diffuse;
	const glm::ivec4* clipRect; // x = left, y = top, z = right, w = bottom
	glm::mat4 model;
};

} // namespace Drawing

#endif // DRAWING_MESH_CREATEINFO_HPP
