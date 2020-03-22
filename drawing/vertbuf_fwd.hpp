#ifndef DRAWING_VERTBUF_FWD_HPP
#define DRAWING_VERTBUF_FWD_HPP
#include <memory>

namespace Drawing
{

namespace Detail
{

class IVertBuf;

} // namespace Detail

using VertBuf = std::shared_ptr<class Detail::IVertBuf>;

} // namespace Drawing

#endif // DRAWING_VERTBUF_FWD_HPP
