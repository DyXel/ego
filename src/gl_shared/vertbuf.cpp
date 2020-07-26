#include "vertbuf.hpp"

#include <type_traits>

#include "common.hpp"

namespace Ego::GLShared
{

VertBuf::VertBuf(BufferHint hint) : hint(GLBufferHintFromEnum(hint))
{
	glGenBuffers(1, &bo);
}

VertBuf::~VertBuf()
{
	glDeleteBuffers(1, &bo);
}

void VertBuf::Submit(const glm::vec3* data, std::size_t size)
{
	const auto bt = sizeof(std::remove_pointer<decltype(data)>::type) * size;
	glBindBuffer(GL_ARRAY_BUFFER, bo);
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(bt), data, hint);
}

} // namespace Ego::GLShared
