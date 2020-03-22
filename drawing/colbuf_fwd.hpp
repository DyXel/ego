#ifndef DRAWING_COLBUF_FWD_HPP
#define DRAWING_COLBUF_FWD_HPP
#include <memory>

namespace Drawing
{

namespace Detail
{

class IColBuf;

} // namespace Detail

using ColBuf = std::shared_ptr<class Detail::IColBuf>;

} // namespace Drawing

#endif // DRAWING_COLBUF_FWD_HPP
