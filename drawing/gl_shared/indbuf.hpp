#ifndef DRAWING_GL_SHARED_INDBUF_HPP
#define DRAWING_GL_SHARED_INDBUF_HPP
#include "gl_include.hpp"
#include "../indbuf.hpp"
#include "../enums.hpp"

namespace Drawing
{

namespace GLShared
{

class IndBuf final : public IIndBuf
{
public:
	GLuint bo; // Buffer Object
	GLsizei count;
	
	IndBuf(BufferHint hint);
	virtual ~IndBuf();
	
	void Submit(const short* data, std::size_t size) override;
private:
	const GLenum hint;
};

} // namespace GLShared

} // namespace Drawing

#endif // DRAWING_GL_SHARED_INDBUF_HPP
