#ifndef DRAWING_VERTBUF_HPP
#define DRAWING_VERTBUF_HPP
#include <glm/vec3.hpp>

#include "submittable.hpp"

namespace Ego
{

class IVertBuf : public Submittable<glm::vec3>
{};

} // namespace Ego

#endif // DRAWING_VERTBUF_HPP
