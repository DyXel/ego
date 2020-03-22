#ifndef DRAWING_UVBUF_HPP
#define DRAWING_UVBUF_HPP
#include <glm/vec2.hpp>

namespace Drawing
{

namespace Detail
{

class IUVBuf
{
public:
	virtual void Submit(const glm::vec2* data, std::size_t length) = 0;
};

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_UVBUF_HPP
