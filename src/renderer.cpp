#include <ego/renderer.hpp>

#include "gl_core/renderer.hpp"

namespace Ego
{

#define OGL_PROC(ret,f,params) \
	do \
	{ \
		(f) = reinterpret_cast<decltype(f)>(glProcAddrGetter(#f)); \
		if(!(f)) \
			return nullptr; \
	}while(0);

SRenderer MakeGLCoreRenderer(Detail::GLProcAddrGetter glProcAddrGetter)
{
#include "gl_shared/gl_core_funcs.inl"
#include "gl_shared/gl_es2_funcs.inl"
	return std::make_shared<GLCore::Renderer>();
}

SRenderer MakeGLESRenderer(Detail::GLProcAddrGetter glProcAddrGetter)
{
#include "gl_shared/gl_es2_funcs.inl"
	return nullptr; // TODO
}

#undef OGL_PROC

} // namespace Ego
