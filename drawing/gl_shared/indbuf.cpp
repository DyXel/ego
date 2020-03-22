#include "indbuf.hpp"

#include <type_traits>

#include "common.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

IndBuf::IndBuf(BufferHint hint) : hint(GLBufferHintFromEnum(hint))
{
	glGenBuffers(1, &bo);
}

IndBuf::~IndBuf()
{
	glDeleteBuffers(1, &bo);
}

void IndBuf::Submit(const short* data, std::size_t size)
{
	count = size;
	const auto bt = sizeof(std::remove_pointer<decltype(data)>::type) * size;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(bt), data, hint);
}

} // namespace GLShared

} // namespace Detail

} // namespace Drawing
