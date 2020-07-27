#define DONT_DEFINE_POINTERS_GL
#include "gl_include.hpp"
#undef DONT_DEFINE_POINTERS_GL

#define OGL_PROC(ret,func,params) ret (APIENTRY *func) params;
#include "gl_core_funcs.inl"
#include "gl_es2_funcs.inl"
#undef OGL_PROC
