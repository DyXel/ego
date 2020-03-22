#include "colbuf.hpp"

#include <type_traits>

#include "common.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

ColBuf::ColBuf(BufferHint hint) : hint(GLBufferHintFromEnum(hint))
{
	glGenBuffers(1, &bo);
}

ColBuf::~ColBuf()
{
	glDeleteBuffers(1, &bo);
}

void ColBuf::Submit(const glm::vec4* data, std::size_t size)
{
	const auto bt = sizeof(std::remove_pointer<decltype(data)>::type) * size;
	glBindBuffer(GL_ARRAY_BUFFER, bo);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(bt), data, hint);
}

} // namespace GLShared

} // namespace Detail

} // namespace Drawing
