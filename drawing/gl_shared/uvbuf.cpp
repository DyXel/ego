#include "uvbuf.hpp"

#include <type_traits>

#include "common.hpp"

namespace Drawing
{

namespace GLShared
{

UVBuf::UVBuf(BufferHint hint) : hint(GLBufferHintFromEnum(hint))
{
	glGenBuffers(1, &bo);
}

UVBuf::~UVBuf()
{
	glDeleteBuffers(1, &bo);
}

void UVBuf::Submit(const glm::vec2* data, std::size_t size)
{
	const auto bt = sizeof(std::remove_pointer<decltype(data)>::type) * size;
	glBindBuffer(GL_ARRAY_BUFFER, bo);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(bt), data, hint);
}

} // namespace GLShared

} // namespace Drawing
