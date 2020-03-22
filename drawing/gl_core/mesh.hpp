#ifndef DRAWING_GL_CORE_MESH_HPP
#define DRAWING_GL_CORE_MESH_HPP
#include "../mesh_createinfo.hpp"
#include "../mesh.hpp"
#include "../gl_shared/common.hpp"
#include "../gl_shared/colbuf.hpp"
#include "../gl_shared/indbuf.hpp"
#include "../gl_shared/vertbuf.hpp"
#include "../gl_shared/uvbuf.hpp"
#include "../gl_shared/texture.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

class Scene;

class Mesh final : public IMesh
{
public:
	GLuint vao{0}; // Vertex Array Object
	GLenum topology;
	bool render;
	bool transparent;
	std::shared_ptr<GLShared::ColBuf> colBuf;
	std::shared_ptr<GLShared::IndBuf> indBuf;
	std::shared_ptr<GLShared::VertBuf> vertBuf;
	std::shared_ptr<GLShared::UVBuf> uvBuf;
	std::shared_ptr<GLShared::Texture> diffuse;
	bool hasScissor;
	GLShared::Rect sci;
	glm::mat4 model;
	Scene* scene{nullptr};
	glm::mat4 mvp; // Model-View-Projection
	
	Mesh(const MeshCreateInfo& info);
	virtual ~Mesh();
	
	void SetTopology(MeshTopology value) override;
	void SetRender(bool value) override;
	void SetTransparent(bool value) override;
	void SetVertBuf(SVertBuf object) override;
	void SetIndBuf(SIndBuf object) override;
	void SetColBuf(SColBuf object) override;
	void SetUVBuf(SUVBuf object) override;
	void SetDiffuse(STexture object) override;
	void SetClipRect(bool has, const glm::vec4& rect) override;
	void SetModelMat4(const glm::mat4& mat) override;
	glm::mat4 GetModelMat4() const override;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_MESH_HPP
