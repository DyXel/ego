#ifndef EGO_GL_CORE_MESH_HPP
#define EGO_GL_CORE_MESH_HPP
#include "../gl_shared/mesh.hpp"
#include "../gl_shared/colbuf.hpp"
#include "../gl_shared/indbuf.hpp"
#include "../gl_shared/vertbuf.hpp"
#include "../gl_shared/uvbuf.hpp"

namespace Ego::GLCore
{

class Mesh final : public GLShared::Mesh
{
public:
	GLuint vao{0}; // Vertex Array Object
	std::shared_ptr<const GLShared::ColBuf> colBuf;
	std::shared_ptr<const GLShared::IndBuf> indBuf;
	std::shared_ptr<const GLShared::VertBuf> vertBuf;
	std::shared_ptr<const GLShared::UVBuf> uvBuf;
	
	Mesh(const MeshCreateInfo& info);
	virtual ~Mesh();
	
	// IMesh overrides
	void SetVertBuf(const SCVertBuf& object) override;
	void SetIndBuf(const SCIndBuf& object) override;
	void SetColBuf(const SCColBuf& object) override;
	void SetUVBuf(const SCUVBuf& object) override;
};

} // namespace Ego::GLCore

#endif // EGO_GL_CORE_MESH_HPP
