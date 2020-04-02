#ifndef EGO_COLBUF_HPP
#define EGO_COLBUF_HPP
#include <glm/vec4.hpp>

#include "submittable.hpp"

namespace Ego
{

class IColBuf : public Submittable<glm::vec4>
{};

} // namespace Ego

#endif // EGO_COLBUF_HPP
