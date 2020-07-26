#ifndef EGO_GL_SHARED_INDBUF_HPP
#define EGO_GL_SHARED_INDBUF_HPP
#include <ego/indbuf.hpp>
#include <ego/enums.hpp>

#include "gl_include.hpp"

namespace Ego::GLShared
{

class IndBuf final : public IIndBuf
{
public:
	GLuint bo{}; // Buffer Object
	GLsizei count{};
	
	IndBuf(BufferHint hint);
	~IndBuf();
	
	void Submit(const short* data, std::size_t size) override;
private:
	const GLenum hint;
};

} // namespace Ego::GLShared

#endif // EGO_GL_SHARED_INDBUF_HPP
