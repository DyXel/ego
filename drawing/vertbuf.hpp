#ifndef EGO_VERTBUF_HPP
#define EGO_VERTBUF_HPP
#include <glm/vec3.hpp>

#include "submittable.hpp"

namespace Ego
{

class IVertBuf : public Submittable<glm::vec3>
{
protected:
	inline ~IVertBuf() = default;
};

} // namespace Ego

#endif // EGO_VERTBUF_HPP
