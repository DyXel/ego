#ifndef DRAWING_MESH_HPP
#define DRAWING_MESH_HPP
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#include "drawing.hpp"
#include "enums.hpp"

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
	virtual void SetVertBuf(SVertBuf object) = 0;
	virtual void SetIndBuf(SIndBuf object) = 0;
	virtual void SetColBuf(SColBuf object) = 0;
	virtual void SetUVBuf(SUVBuf object) = 0;
	virtual void SetDiffuse(STexture object) = 0;
	virtual void SetClipRect(bool has, const glm::vec4& rect) = 0;
	virtual void SetModelMat4(const glm::mat4& mat) = 0;
	virtual glm::mat4 GetModelMat4() const = 0;
};

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_MESH_HPP
