#ifndef EGO_GL_SHARED_VERTBUF_HPP
#define EGO_GL_SHARED_VERTBUF_HPP
#include <ego/enums.hpp>
#include <ego/vertbuf.hpp>

#include "gl_include.hpp"

namespace Ego::GLShared
{

class VertBuf final : public IVertBuf
{
public:
	GLuint bo{}; // Buffer Object
	
	VertBuf(BufferHint hint);
	~VertBuf();
	
	void Submit(const glm::vec3* data, std::size_t size) override;
private:
	const GLenum hint;
};

} // namespace Ego::GLShared

#endif // EGO_GL_SHARED_VERTBUF_HPP
