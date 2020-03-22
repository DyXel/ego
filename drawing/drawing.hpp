#ifndef DRAWING_DRAWING_HPP
#define DRAWING_DRAWING_HPP
#include <memory>

namespace Drawing
{

#define FORWARD_DECLARE(name) \
	namespace Detail { class I##name; } \
	using S##name = std::shared_ptr<class Detail::I##name>; \
	using W##name = std::weak_ptr<class Detail::I##name>
// 	using name = Detail::I##name

FORWARD_DECLARE(ColBuf);
FORWARD_DECLARE(IndBuf);
FORWARD_DECLARE(Mesh);
FORWARD_DECLARE(Renderer);
FORWARD_DECLARE(Scene);
FORWARD_DECLARE(Texture);
FORWARD_DECLARE(UVBuf);
FORWARD_DECLARE(VertBuf);

#undef FORWARD_DECLARE

} // namespace Drawing

#endif // DRAWING_DRAWING_HPP
