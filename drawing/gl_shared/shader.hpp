#ifndef DRAWING_GL_SHARED_SHADER_HPP
#define DRAWING_GL_SHARED_SHADER_HPP
#include <string_view>
#include "gl_include.hpp"

namespace Drawing
{

namespace GLShared
{

class Shader
{
public:
	bool compiled;
	GLenum type;
	GLuint so; // Shader Object
	
	Shader(const GLenum type, std::string_view source);
	~Shader();
};

} // GLShared

} // Drawing

#endif // DRAWING_GL_SHARED_SHADER_HPP
