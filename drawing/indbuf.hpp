#ifndef DRAWING_INDBUF_HPP
#define DRAWING_INDBUF_HPP
#include "submittable.hpp"

namespace Drawing
{

namespace Detail
{

class IIndBuf : public Submittable<short>
{};

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_INDBUF_HPP
