#ifndef DRAWING_INDBUF_HPP
#define DRAWING_INDBUF_HPP
#include <cstddef> // std::size_t

namespace Drawing
{

namespace Detail
{

class IIndBuf
{
public:
	virtual void Submit(const short* data, std::size_t length) = 0;
};

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_INDBUF_HPP
