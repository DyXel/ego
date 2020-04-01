#include "cache.hpp"

namespace Drawing
{

namespace GLShared
{

Cache::Cache()
{
	Reset();
}

void Cache::Reset()
{
	blend = false;
	glDisable(GL_BLEND);
	depthTest = false;
	glDisable(GL_DEPTH_TEST);
	scissorTest = false;
	glDisable(GL_SCISSOR_TEST);
	cullFace = false;
	glDisable(GL_CULL_FACE);
	
	glBlendFunc(blendSFactor = GL_ONE, blendDFactor = GL_ZERO);
	glUseProgram(program = 0);
}

void Cache::SetBlending(bool enabled)
{
	if(blend == enabled)
		return;
	if((blend = enabled))
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
}

void Cache::SetDepthTest(bool enabled)
{
	if(depthTest == enabled)
		return;
	if((depthTest = enabled))
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void Cache::SetScissorTest(bool enabled)
{
	if(scissorTest == enabled)
		return;
	if((scissorTest = enabled))
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

void Cache::SetCullFace(bool enabled)
{
	if(cullFace == enabled)
		return;
	if((cullFace = enabled))
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void Cache::SetBlendFunc(GLenum sFactor, GLenum dFactor)
{
	if(blendSFactor == sFactor && blendDFactor == dFactor)
		return;
	glBlendFunc(blendSFactor = sFactor, blendDFactor = dFactor);
}

void Cache::UseProgram(GLuint spo)
{
	if(program == spo)
		return;
	glUseProgram(program = spo);
}

} // namespace Drawing

} // namespace GLShared
