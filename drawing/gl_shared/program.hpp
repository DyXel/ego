#ifndef EGO_GL_SHARED_PROGRAM_HPP
#define EGO_GL_SHARED_PROGRAM_HPP
#include <array>
#include <glm/mat4x4.hpp>

#include "gl_include.hpp"
#include "common.hpp"

namespace Ego
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

#endif // EGO_GL_SHARED_PROGRAM_HPP
