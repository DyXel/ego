#ifndef EGO_GL_SHARED_UVBUF_HPP
#define EGO_GL_SHARED_UVBUF_HPP
#include "gl_include.hpp"
#include "../enums.hpp"
#include "../uvbuf.hpp"

namespace Ego
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

} // namespace Ego

#endif // EGO_GL_SHARED_UVBUF_HPP
