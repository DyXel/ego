#ifndef EGO_GL_SHARED_COLBUF_HPP
#define EGO_GL_SHARED_COLBUF_HPP
#include <ego/enums.hpp>
#include <ego/colbuf.hpp>

#include "gl_include.hpp"

namespace Ego::GLShared
{

class ColBuf final : public IColBuf
{
public:
	GLuint bo{}; // Buffer Object
	
	ColBuf(BufferHint hint);
	~ColBuf();
	
	void Submit(const glm::vec4* data, std::size_t size) override;
private:
	const GLenum hint;
};

} // namespace Ego::GLShared

#endif // EGO_GL_SHARED_COLBUF_HPP
