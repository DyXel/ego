#include "mesh.hpp"

#include "../gl_shared/common.hpp"

namespace Ego::GLES
{

Mesh::Mesh(const MeshCreateInfo& info) : GLShared::Mesh(info)
{
	SetVertBuf(info.vertBuf);
	SetIndBuf(info.indBuf);
	SetColBuf(info.colBuf);
	SetUVBuf(info.uvBuf);
}

void Mesh::SetVertBuf(const SCVertBuf& object)
{
	using namespace GLShared;
	vertBuf = std::dynamic_pointer_cast<const VertBuf>(object);
}

void Mesh::SetIndBuf(const SCIndBuf& object)
{
	using namespace GLShared;
	indBuf = std::dynamic_pointer_cast<const IndBuf>(object);
}

void Mesh::SetColBuf(const SCColBuf& object)
{
	using namespace GLShared;
	colBuf = std::dynamic_pointer_cast<const ColBuf>(object);
}

void Mesh::SetUVBuf(const SCUVBuf& object)
{
	using namespace GLShared;
	uvBuf = std::dynamic_pointer_cast<const UVBuf>(object);
}

} // namespace Ego::GLES
