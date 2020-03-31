#ifndef DRAWING_GL_SHARED_UVBUF_HPP
#define DRAWING_GL_SHARED_UVBUF_HPP
#include "gl_include.hpp"
#include "../enums.hpp"
#include "../uvbuf.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class UVBuf final : public IUVBuf
{
public:
	GLuint bo; // Buffer Object
	
	UVBuf(BufferHint hint);
	virtual ~UVBuf();
	
	void Submit(const glm::vec2* data, std::size_t size) override;
private:
	const GLenum hint;
};

} // namespace GLShared

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_SHARED_UVBUF_HPP
