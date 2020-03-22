#include "program.hpp"
#include <SDL_log.h>

#include "common.hpp"
#include "shader.hpp"

#include <glm/gtc/type_ptr.hpp>

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

Program::Program()
{
	spo = glCreateProgram();
	if(spo == 0)
		return;
}

Program::~Program()
{
	// NOTE: From reference: A value of 0 for spo will be silently ignored.
	glDeleteProgram(spo);
}

void Program::Attach(const Shader& shader)
{
	glAttachShader(spo, shader.so);
}

bool Program::Link()
{
	// Bind attribute names to their indexes
	for(std::size_t i = 0; i < ATTRIBUTE_COUNT; i++)
		glBindAttribLocation(spo, static_cast<GLuint>(i), ATTRIBUTE_NAMES[i]);
	// Link program
	glLinkProgram(spo);
	GLint success;
	glGetProgramiv(spo, GL_LINK_STATUS, &success);
	if(success == GL_FALSE)
	{
		GLint logLength;
		glGetProgramiv(spo, GL_INFO_LOG_LENGTH, &logLength);
		auto logText = new char[static_cast<std::size_t>(logLength)];
		glGetProgramInfoLog(spo, logLength, nullptr, logText);
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
		             "Could not link program: %s", logText);
		delete[] logText;
		return false;
	}
	// Get uniform locations (if it has them)
	for(std::size_t i = 0; i < UNIFORM_COUNT; i++)
		uni[i] = glGetUniformLocation(spo, UNIFORM_NAMES[i]);
	return true;
}

GLint Program::GetUniformLocation(Uniform name) const
{
	return uni[name];
}

}  // namespace GLShared

}  // namespace Detail

}  // namespace Drawing
