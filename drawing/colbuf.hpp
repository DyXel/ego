#ifndef DRAWING_COLBUF_HPP
#define DRAWING_COLBUF_HPP
#include <glm/vec4.hpp>

namespace Drawing
{

namespace Detail
{

class IColBuf
{
public:
	virtual void Submit(const glm::vec4* data, std::size_t length) = 0;
};

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_COLBUF_HPP
