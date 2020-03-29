#ifndef DRAWING_GL_SHARED_MESH_HPP
#define DRAWING_GL_SHARED_MESH_HPP
#include "../mesh_createinfo.hpp"
#include "../mesh.hpp"
#include "common.hpp"
#include "texture.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class Scene;

class Mesh : public IMesh
{
public:
	Scene* scene;
	GLenum topology;
	bool render;
	bool transparent;
	std::shared_ptr<Texture> diffuse;
	bool hasScissor;
	Rect sci;
	glm::mat4 model;
	glm::mat4 mvp; // Model-View-Projection matrix
	
	Mesh(const MeshCreateInfo& info);
	virtual ~Mesh() = default;
	
	// Drawing::Detail::IMesh overrides
	void SetTopology(MeshTopology value) override;
	void SetRender(bool value) override;
	void SetTransparent(bool value) override;
	void SetDiffuse(STexture object) override;
	void SetClipRect(bool has, const glm::vec4& rect) override;
	void SetModelMat4(const glm::mat4& mat) override;
	glm::mat4 GetModelMat4() const override;
};

} // namespace GLShared

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_SHARED_MESH_HPP
