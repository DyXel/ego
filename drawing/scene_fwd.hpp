#ifndef DRAWING_SCENE_FWD_HPP
#define DRAWING_SCENE_FWD_HPP
#include <memory>

namespace Drawing
{

namespace Detail
{

class IScene;

} // namespace Detail

using Scene = std::shared_ptr<class Detail::IScene>;

} // namespace Drawing

#endif // DRAWING_SCENE_FWD_HPP
