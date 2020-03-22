#ifndef DRAWING_GL_SHARED_INDBUF_HPP
#define DRAWING_GL_SHARED_INDBUF_HPP
#include "../indbuf.hpp"
#include "../enums.hpp"

#include "gl_include.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class IndBuf final : public IIndBuf
{
public:
	GLuint bo{0}; // Buffer Object
	GLsizei count;
	
	IndBuf(BufferHint hint);
	virtual ~IndBuf();
	
	void Submit(const short* data, std::size_t size) override;
private:
	const GLenum hint;
};

} // namespace GLShared

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_SHARED_INDBUF_HPP
