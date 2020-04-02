#include "shader.hpp"
#include <SDL_log.h>

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
	{
		GLint logLength;
		glGetShaderiv(so, GL_INFO_LOG_LENGTH, &logLength);
		auto logText = new char[static_cast<std::size_t>(logLength)];
		glGetShaderInfoLog(so, logLength, nullptr, logText);
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Could not compile shader: %s", logText);
		delete[] logText;
		return;
	}
	compiled = true;
}

Shader::~Shader()
{
	// NOTE: From reference: A value of 0 for so will be silently ignored.
	glDeleteShader(so);
}

}  // namespace Ego::GLShared
