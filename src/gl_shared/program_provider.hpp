#ifndef EGO_GL_SHARED_PROGRAM_PROVIDER_HPP
#define EGO_GL_SHARED_PROGRAM_PROVIDER_HPP
#include "program.hpp"

namespace Ego::GLShared
{

enum ProgramTypes
{
	PROGRAM_ONLY_COLOR = 0,
	PROGRAM_TEXTURE_PLUS_COLOR,
	PROGRAM_TYPES_COUNT
};

class IProgramProvider
{
public:
	virtual const Program& GetProgram(ProgramTypes value) const = 0;
protected:
	inline ~IProgramProvider() = default;
};

} // namespace Ego::GLShared

#endif // EGO_GL_SHARED_PROGRAM_PROVIDER_HPP
