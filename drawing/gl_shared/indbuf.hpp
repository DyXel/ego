#ifndef EGO_GL_SHARED_INDBUF_HPP
#define EGO_GL_SHARED_INDBUF_HPP
#include "gl_include.hpp"
#include "../indbuf.hpp"
#include "../enums.hpp"

namespace Ego
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

} // namespace Ego

#endif // EGO_GL_SHARED_INDBUF_HPP
