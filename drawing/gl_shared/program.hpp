#ifndef DRAWING_GL_SHARED_PROGRAM_HPP
#define DRAWING_GL_SHARED_PROGRAM_HPP
#include <array>
#include <glm/mat4x4.hpp>

#include "gl_include.hpp"
#include "common.hpp"

namespace Drawing
{

namespace GLShared
{

class Shader;

class Program
{
public:
	GLuint spo; // Shader Program Object
	
	Program();
	~Program();
	
	void Attach(const Shader& shader);
	bool Link();
	
	GLint GetUniformLocation(Uniform name) const;
private:
	std::array<GLint, UNIFORM_COUNT> uni{};
};

} // GLShared

} // Drawing

#endif // DRAWING_GL_SHARED_PROGRAM_HPP
