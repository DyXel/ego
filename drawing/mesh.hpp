#ifndef DRAWING_MESH_HPP
#define DRAWING_MESH_HPP
#include "enums.hpp"
#include "colbuf_fwd.hpp"
#include "indbuf_fwd.hpp"
#include "uvbuf_fwd.hpp"
#include "texture_fwd.hpp"
#include "vertbuf_fwd.hpp"

namespace Drawing
{

namespace Detail
{

class IMesh
{
public:
	virtual ~IMesh() = default;
	
	virtual void SetTopology(MeshTopology value) = 0;
	virtual void SetRender(bool value) = 0;
	virtual void SetTransparent(bool value) = 0;
	virtual void SetVertBuf(VertBuf object) = 0;
	virtual void SetIndBuf(IndBuf object) = 0;
	virtual void SetColBuf(ColBuf object) = 0;
	virtual void SetUVBuf(UVBuf object) = 0;
	virtual void SetDiffuse(Texture object) = 0;
	virtual void SetClipRect(bool has, const glm::vec4& rect) = 0;
	virtual void SetModelMat4(const glm::mat4& mat) = 0;
	virtual glm::mat4 GetModelMat4() const = 0;
};

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_MESH_HPP
