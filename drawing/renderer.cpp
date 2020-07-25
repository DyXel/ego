#include "renderer.hpp"

#include "gl_core/renderer.hpp"

namespace Ego
{

#define SDL_PROC(ret,f,params) \
	do \
	{ \
		(f) = reinterpret_cast<decltype(f)>(glProcAddrGetter(#f)); \
		if(!(f)) \
			return nullptr; \
	}while(0);

SRenderer MakeGLCoreRenderer(Detail::GLProcAddrGetter glProcAddrGetter)
{
#ifndef USE_PROTOTYPES_GL
#include "gl_shared/gl_core_funcs.inl"
#include "gl_shared/gl_es2_funcs.inl"
#endif
	return std::make_shared<GLCore::Renderer>();
}

SRenderer MakeGLESRenderer(Detail::GLProcAddrGetter glProcAddrGetter)
{
#ifndef USE_PROTOTYPES_GL
#include "gl_shared/gl_es2_funcs.inl"
#endif
	return nullptr; // TODO
}

#undef SDL_PROC

} // namespace Ego