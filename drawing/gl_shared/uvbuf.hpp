#ifndef DRAWING_GL_SHARED_UVBUF_HPP
#define DRAWING_GL_SHARED_UVBUF_HPP
#include "../uvbuf.hpp"
#include "../enums.hpp"

#include "gl_include.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class UVBuf final : public IUVBuf
{
public:
	GLuint bo{0}; // Buffer Object
	
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
