#ifndef EGO_GL_SHARED_CACHE_HPP
#define EGO_GL_SHARED_CACHE_HPP
#include "gl_include.hpp"

namespace Ego::GLShared
{

class Cache
{
public:
	Cache();
	void Reset();
	
	void SetBlending(bool enabled);
	void SetDepthTest(bool enabled);
	void SetScissorTest(bool enabled);
	void SetCullFace(bool enabled);
	
	void SetBlendFunc(GLenum sFactor, GLenum dFactor);
	void UseProgram(GLuint spo);
private:
	bool blend{};
	bool depthTest{};
	bool scissorTest{};
	bool cullFace{};
	GLenum blendSFactor{}, blendDFactor{};
	GLuint program{};
};

} // namespace Ego::GLShared

#endif // EGO_GL_SHARED_CACHE_HPP
