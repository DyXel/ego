#ifndef DRAWING_VERTBUF_HPP
#define DRAWING_VERTBUF_HPP
#include <glm/vec3.hpp>

namespace Drawing
{

namespace Detail
{

class IVertBuf
{
public:
	virtual void Submit(const glm::vec3* data, std::size_t length) = 0;
};

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_VERTBUF_HPP
