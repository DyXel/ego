#ifndef DRAWING_GL_SHARED_COLBUF_HPP
#define DRAWING_GL_SHARED_COLBUF_HPP
#include "../colbuf.hpp"
#include "../enums.hpp"

#include "gl_include.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class ColBuf final : public IColBuf
{
public:
	GLuint bo{0}; // Buffer Object
	
	ColBuf(BufferHint hint);
	virtual ~ColBuf();
	
	void Submit(const glm::vec4* data, std::size_t size) override;
private:
	const GLenum hint;
};

} // namespace GLShared

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_SHARED_COLBUF_HPP
