#ifndef DRAWING_COLBUF_HPP
#define DRAWING_COLBUF_HPP
#include <glm/vec4.hpp>

#include "submittable.hpp"

namespace Ego
{

class IColBuf : public Submittable<glm::vec4>
{};

} // namespace Ego

#endif // DRAWING_COLBUF_HPP
