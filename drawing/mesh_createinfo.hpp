#ifndef DRAWING_MESH_CREATEINFO_HPP
#define DRAWING_MESH_CREATEINFO_HPP
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "drawing.hpp"
#include "enums.hpp"

namespace Drawing
{

struct MeshCreateInfo
{
	MeshTopology topology;
	bool render;
	bool transparent;
	SVertBuf vertBuf;
	SIndBuf indBuf;
	SColBuf colBuf;
	SUVBuf uvBuf;
	STexture diffuse;
	bool hasClipRect;
	glm::vec4 clipRect; // x = left, y = top, z = right, w = bottom
	glm::mat4 model;
};

} // namespace Drawing

#endif // DRAWING_MESH_CREATEINFO_HPP
