#ifndef DRAWING_GL_SHARED_COLBUF_HPP
#define DRAWING_GL_SHARED_COLBUF_HPP
#include "gl_include.hpp"
#include "../enums.hpp"
#include "../colbuf.hpp"

namespace Ego
{

namespace GLShared
{

class ColBuf final : public IColBuf
{
public:
	GLuint bo; // Buffer Object
	
	ColBuf(BufferHint hint);
	virtual ~ColBuf();
	
	void Submit(const glm::vec4* data, std::size_t size) override;
private:
	const GLenum hint;
};

} // namespace GLShared

} // namespace Ego

#endif // DRAWING_GL_SHARED_COLBUF_HPP
