#ifndef DRAWING_INDBUF_FWD_HPP
#define DRAWING_INDBUF_FWD_HPP
#include <memory>

namespace Drawing
{

namespace Detail
{

class IIndBuf;

} // namespace Detail

using IndBuf = std::shared_ptr<class Detail::IIndBuf>;

} // namespace Drawing

#endif // DRAWING_INDBUF_FWD_HPP
