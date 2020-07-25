#include "shader.hpp"

namespace Ego::GLShared
{

Shader::Shader(const GLenum type, std::string_view source) :
	compiled(false),
	type(type),
	so(glCreateShader(type))
{
	if(so == 0)
		return;
	const char* src[] = {source.data()};
	glShaderSource(so, 1, src, nullptr);
	glCompileShader(so);
	GLint success;
	glGetShaderiv(so, GL_COMPILE_STATUS, &success);
	if(success == GL_FALSE)
		return;
	compiled = true;
}

Shader::~Shader()
{
	// NOTE: From reference: A value of 0 for so will be silently ignored.
	glDeleteShader(so);
}

}  // namespace Ego::GLShared
