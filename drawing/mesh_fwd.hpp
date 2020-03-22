#ifndef DRAWING_MESH_FWD_HPP
#define DRAWING_MESH_FWD_HPP
#include <memory>

namespace Drawing
{

namespace Detail
{

class IMesh;

} // namespace Detail

using Mesh = std::shared_ptr<class Detail::IMesh>;

} // namespace Drawing

#endif // DRAWING_MESH_FWD_HPP
