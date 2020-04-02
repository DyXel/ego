#ifndef EGO_EGO_HPP
#define EGO_EGO_HPP
#include <memory>

namespace Ego
{

#define FORWARD_DECLARE(name) \
	class I##name; \
	using S##name = std::shared_ptr<class I##name>; \
	using SC##name = std::shared_ptr<const class I##name>

FORWARD_DECLARE(ColBuf);
FORWARD_DECLARE(IndBuf);
FORWARD_DECLARE(Mesh);
FORWARD_DECLARE(Renderer);
FORWARD_DECLARE(Scene);
FORWARD_DECLARE(Texture);
FORWARD_DECLARE(UVBuf);
FORWARD_DECLARE(VertBuf);

#undef FORWARD_DECLARE

} // namespace Ego

#endif // EGO_EGO_HPP
