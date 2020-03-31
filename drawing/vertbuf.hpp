#ifndef DRAWING_VERTBUF_HPP
#define DRAWING_VERTBUF_HPP
#include <glm/vec3.hpp>

#include "submittable.hpp"

namespace Drawing
{

class IVertBuf : public Submittable<glm::vec3>
{};

} // namespace Drawing

#endif // DRAWING_VERTBUF_HPP
