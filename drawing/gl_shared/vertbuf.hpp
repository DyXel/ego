#ifndef DRAWING_GL_SHARED_VERTBUF_HPP
#define DRAWING_GL_SHARED_VERTBUF_HPP
#include "gl_include.hpp"
#include "../enums.hpp"
#include "../vertbuf.hpp"

namespace Drawing
{

namespace GLShared
{

class VertBuf final : public IVertBuf
{
public:
	GLuint bo; // Buffer Object
	
	VertBuf(BufferHint hint);
	virtual ~VertBuf();
	
	void Submit(const glm::vec3* data, std::size_t size) override;
private:
	const GLenum hint;
};

} // namespace GLShared

} // namespace Drawing

#endif // DRAWING_GL_SHARED_VERTBUF_HPP
