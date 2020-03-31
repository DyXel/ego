#ifndef DRAWING_UVBUF_HPP
#define DRAWING_UVBUF_HPP
#include <glm/vec2.hpp>

#include "submittable.hpp"

namespace Drawing
{

class IUVBuf : public Submittable<glm::vec2>
{};

} // namespace Drawing

#endif // DRAWING_UVBUF_HPP
