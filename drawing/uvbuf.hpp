#ifndef EGO_UVBUF_HPP
#define EGO_UVBUF_HPP
#include <glm/vec2.hpp>

#include "submittable.hpp"

namespace Ego
{

class IUVBuf : public Submittable<glm::vec2>
{};

} // namespace Ego

#endif // EGO_UVBUF_HPP
