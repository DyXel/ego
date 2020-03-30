#ifndef DRAWING_GL_SHARED_PROGRAM_PROVIDER_HPP
#define DRAWING_GL_SHARED_PROGRAM_PROVIDER_HPP
#include "program.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
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
};

} // namespace GLShared

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_SHARED_PROGRAM_PROVIDER_HPP
