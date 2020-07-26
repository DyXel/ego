#ifndef EGO_MESH_CREATEINFO_HPP
#define EGO_MESH_CREATEINFO_HPP
#include <glm/mat4x4.hpp>
#include <glm/ext/vector_int4.hpp>

#include "ego_fwd.hpp"
#include "enums.hpp"

namespace Ego
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

} // namespace Ego

#endif // EGO_MESH_CREATEINFO_HPP
