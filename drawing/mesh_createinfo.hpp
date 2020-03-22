#ifndef DRAWING_MESH_CREATEINFO_HPP
#define DRAWING_MESH_CREATEINFO_HPP
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include "enums.hpp"
#include "colbuf_fwd.hpp"
#include "indbuf_fwd.hpp"
#include "texture_fwd.hpp"
#include "uvbuf_fwd.hpp"
#include "vertbuf_fwd.hpp"

namespace Drawing
{

struct MeshCreateInfo
{
	MeshTopology topology;
	bool render;
	bool transparent;
	VertBuf vertBuf;
	IndBuf indBuf;
	ColBuf colBuf;
	UVBuf uvBuf;
	Texture diffuse;
	bool hasClipRect;
	glm::vec4 clipRect; // x = left, y = top, z = right, w = bottom
	glm::mat4 model;
};

} // namespace Drawing

#endif // DRAWING_MESH_CREATEINFO_HPP
