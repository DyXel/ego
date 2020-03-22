#ifndef DRAWING_GL_SHARED_SHADER_HPP
#define DRAWING_GL_SHARED_SHADER_HPP
#include <string_view>
#include "gl_include.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class Shader
{
public:
	bool compiled{false};
	GLenum type;
	GLuint so; // Shader Object
	
	Shader(const GLenum type, std::string_view source);
	~Shader();
};

} // GLShared

} // Detail

} // Drawing

#endif // DRAWING_GL_SHARED_SHADER_HPP
