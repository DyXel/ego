#ifndef DRAWING_GL_CORE_MESH_HPP
#define DRAWING_GL_CORE_MESH_HPP
#include "../gl_shared/mesh.hpp"
#include "../gl_shared/colbuf.hpp"
#include "../gl_shared/indbuf.hpp"
#include "../gl_shared/vertbuf.hpp"
#include "../gl_shared/uvbuf.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

class Mesh final : public GLShared::Mesh
{
public:
	GLuint vao{0}; // Vertex Array Object
	std::shared_ptr<GLShared::ColBuf> colBuf;
	std::shared_ptr<GLShared::IndBuf> indBuf;
	std::shared_ptr<GLShared::VertBuf> vertBuf;
	std::shared_ptr<GLShared::UVBuf> uvBuf;
	
	Mesh(const MeshCreateInfo& info);
	virtual ~Mesh();
	
	// Drawing::Detail::IMesh overrides
	void SetVertBuf(SVertBuf object) override;
	void SetIndBuf(SIndBuf object) override;
	void SetColBuf(SColBuf object) override;
	void SetUVBuf(SUVBuf object) override;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_MESH_HPP
