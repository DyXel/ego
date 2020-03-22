#ifndef DRAWING_TEXTURE_FWD_HPP
#define DRAWING_TEXTURE_FWD_HPP
#include <memory>

namespace Drawing
{

namespace Detail
{

class ITexture;

} // namespace Detail

using Texture = std::shared_ptr<class Detail::ITexture>;

} // namespace Drawing

#endif // DRAWING_TEXTURE_FWD_HPP
