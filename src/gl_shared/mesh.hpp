#ifndef EGO_GL_SHARED_MESH_HPP
#define EGO_GL_SHARED_MESH_HPP
#include <ego/mesh_createinfo.hpp>
#include <ego/mesh.hpp>

#include "common.hpp"
#include "texture.hpp"

namespace Ego::GLShared
{

class IMeshListener;

class Mesh : public IMesh
{
public:
	IMeshListener* listener;
	GLenum topology{};
	bool render{};
	bool transparent{};
	std::shared_ptr<const Texture> diffuse;
	bool hasScissor{};
	glm::ivec4 sci{};
	glm::mat4 model{};
	glm::mat4 mvp{}; // Model-View-Projection matrix
	
	Mesh(const MeshCreateInfo& info);
	
	// IMesh overrides
	void SetTopology(MeshTopology value) override;
	void SetRender(bool value) override;
	void SetTransparent(bool value) override;
	void SetDiffuse(const SCTexture& object) override;
	void SetClipRect(const glm::ivec4* rect) override;
	void SetModelMat4(const glm::mat4& mat) override;
	glm::mat4 GetModelMat4() const override;
};

} // namespace Ego::GLShared

#endif // EGO_GL_SHARED_MESH_HPP
