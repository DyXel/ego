#ifndef EGO_INDBUF_HPP
#define EGO_INDBUF_HPP
#include "submittable.hpp"

namespace Ego
{

class IIndBuf : public Submittable<short>
{
protected:
	inline ~IIndBuf() = default;
};

} // namespace Ego

#endif // EGO_INDBUF_HPP
