#ifndef DRAWING_COLBUF_HPP
#define DRAWING_COLBUF_HPP
#include <glm/vec4.hpp>

#include "submittable.hpp"

namespace Drawing
{

namespace Detail
{

class IColBuf : public Submittable<glm::vec4>
{};

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_COLBUF_HPP
