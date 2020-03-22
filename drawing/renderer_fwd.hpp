#ifndef DRAWING_RENDERER_FWD_HPP
#define DRAWING_RENDERER_FWD_HPP
#include <memory>

namespace Drawing
{

namespace Detail
{

class IRenderer;

} // namespace Detail

using Renderer = std::shared_ptr<class Detail::IRenderer>;

} // namespace Drawing

#endif // DRAWING_RENDERER_FWD_HPP
