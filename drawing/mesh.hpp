#ifndef DRAWING_MESH_HPP
#define DRAWING_MESH_HPP
#include <glm/mat4x4.hpp>
#include <glm/ext/vector_int4.hpp>

#include "drawing.hpp"
#include "enums.hpp"

namespace Drawing
{

class IMesh
{
public:
	virtual ~IMesh() = default;
	
	virtual void SetTopology(MeshTopology value) = 0;
	virtual void SetRender(bool value) = 0;
	virtual void SetTransparent(bool value) = 0;
	virtual void SetVertBuf(const SCVertBuf& object) = 0;
	virtual void SetIndBuf(const SCIndBuf& object) = 0;
	virtual void SetColBuf(const SCColBuf& object) = 0;
	virtual void SetUVBuf(const SCUVBuf& object) = 0;
	virtual void SetDiffuse(const SCTexture& object) = 0;
	virtual void SetClipRect(const glm::ivec4* rect) = 0;
	virtual void SetModelMat4(const glm::mat4& mat) = 0;
	virtual glm::mat4 GetModelMat4() const = 0;
};

} // namespace Drawing

#endif // DRAWING_MESH_HPP
