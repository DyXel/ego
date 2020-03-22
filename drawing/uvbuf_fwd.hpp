#ifndef DRAWING_UVBUF_FWD_HPP
#define DRAWING_UVBUF_FWD_HPP
#include <memory>

namespace Drawing
{

namespace Detail
{

class IUVBuf;

} // namespace Detail

using UVBuf = std::shared_ptr<class Detail::IUVBuf>;

} // namespace Drawing

#endif // DRAWING_UVBUF_FWD_HPP
