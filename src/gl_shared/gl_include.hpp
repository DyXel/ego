#ifndef GL_INCLUDE_HPP
#define GL_INCLUDE_HPP
#include "gl_include_defines.h"

// The following system-specific code was taken from SDL2 source code.
// Specifically: include/SDL_platform.h and include/SDL_opengl.h

/**********************************************************************
 * Begin system-specific stuff.
 */

#if defined(_AIX)
#undef __AIX__
#define __AIX__     1
#endif
#if defined(__HAIKU__)
#undef __HAIKU__
#define __HAIKU__   1
#endif
#if defined(bsdi) || defined(__bsdi) || defined(__bsdi__)
#undef __BSDI__
#define __BSDI__    1
#endif
#if defined(_arch_dreamcast)
#undef __DREAMCAST__
#define __DREAMCAST__   1
#endif
#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__DragonFly__)
#undef __FREEBSD__
#define __FREEBSD__ 1
#endif
#if defined(hpux) || defined(__hpux) || defined(__hpux__)
#undef __HPUX__
#define __HPUX__    1
#endif
#if defined(sgi) || defined(__sgi) || defined(__sgi__) || defined(_SGI_SOURCE)
#undef __IRIX__
#define __IRIX__    1
#endif
#if (defined(linux) || defined(__linux) || defined(__linux__))
#undef __LINUX__
#define __LINUX__   1
#endif
#if defined(ANDROID) || defined(__ANDROID__)
#undef __ANDROID__
#undef __LINUX__ /* do we need to do this? */
#define __ANDROID__ 1
#endif

#if defined(__APPLE__)
/* lets us know what version of Mac OS X we're compiling on */
#include "AvailabilityMacros.h"
#include "TargetConditionals.h"
#if TARGET_OS_TV
#undef __TVOS__
#define __TVOS__ 1
#endif
#if TARGET_OS_IPHONE
/* if compiling for iOS */
#undef __IPHONEOS__
#define __IPHONEOS__ 1
#undef __MACOSX__
#else
/* if not compiling for iOS */
#undef __MACOSX__
#define __MACOSX__  1
#if MAC_OS_X_VERSION_MIN_REQUIRED < 1060
# error SDL for Mac OS X only supports deploying on 10.6 and above.
#endif /* MAC_OS_X_VERSION_MIN_REQUIRED < 1060 */
#endif /* TARGET_OS_IPHONE */
#endif /* defined(__APPLE__) */

#if defined(__NetBSD__)
#undef __NETBSD__
#define __NETBSD__  1
#endif
#if defined(__OpenBSD__)
#undef __OPENBSD__
#define __OPENBSD__ 1
#endif
#if defined(__OS2__) || defined(__EMX__)
#undef __OS2__
#define __OS2__     1
#endif
#if defined(osf) || defined(__osf) || defined(__osf__) || defined(_OSF_SOURCE)
#undef __OSF__
#define __OSF__     1
#endif
#if defined(__QNXNTO__)
#undef __QNXNTO__
#define __QNXNTO__  1
#endif
#if defined(riscos) || defined(__riscos) || defined(__riscos__)
#undef __RISCOS__
#define __RISCOS__  1
#endif
#if defined(__sun) && defined(__SVR4)
#undef __SOLARIS__
#define __SOLARIS__ 1
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
/* Try to find out if we're compiling for WinRT or non-WinRT */
#if defined(_MSC_VER) && defined(__has_include)
#if __has_include(<winapifamily.h>)
#define HAVE_WINAPIFAMILY_H 1
#else
#define HAVE_WINAPIFAMILY_H 0
#endif

/* If _USING_V110_SDK71_ is defined it means we are using the Windows XP toolset. */
#elif defined(_MSC_VER) && (_MSC_VER >= 1700 && !_USING_V110_SDK71_)    /* _MSC_VER == 1700 for Visual Studio 2012 */
#define HAVE_WINAPIFAMILY_H 1
#else
#define HAVE_WINAPIFAMILY_H 0
#endif

#if HAVE_WINAPIFAMILY_H
#include <winapifamily.h>
#define WINAPI_FAMILY_WINRT (!WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP) && WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP))
#else
#define WINAPI_FAMILY_WINRT 0
#endif /* HAVE_WINAPIFAMILY_H */

#if WINAPI_FAMILY_WINRT
#undef __WINRT__
#define __WINRT__ 1
#else
#undef __WINDOWS__
#define __WINDOWS__ 1
#endif
#endif /* defined(WIN32) || defined(_WIN32) || defined(__CYGWIN__) */

#if defined(__WINDOWS__)
#undef __WIN32__
#define __WIN32__ 1
#endif
#if defined(__PSP__)
#undef __PSP__
#define __PSP__ 1
#endif

/* The NACL compiler defines __native_client__ and __pnacl__
 * Ref: http://www.chromium.org/nativeclient/pnacl/stability-of-the-pnacl-bitcode-abi
 */
#if defined(__native_client__)
#undef __LINUX__
#undef __NACL__
#define __NACL__ 1
#endif
#if defined(__pnacl__)
#undef __LINUX__
#undef __PNACL__
#define __PNACL__ 1
/* PNACL with newlib supports static linking only */
#define __SDL_NOGETPROCADDR__
#endif

#if defined(_WIN32) && !defined(__WIN32__) && !defined(__CYGWIN__)
#define __WIN32__
#endif

#if defined(__WIN32__) && !defined(__CYGWIN__)
#  if (defined(_MSC_VER) || defined(__MINGW32__)) && defined(BUILD_GL32) /* tag specify we're building mesa as a DLL */
#    define GLAPI __declspec(dllexport)
#  elif (defined(_MSC_VER) || defined(__MINGW32__)) && defined(_DLL) /* tag specifying we're building for DLL runtime support */
#    define GLAPI __declspec(dllimport)
#  else /* for use with static link lib build of Win32 edition only */
#    define GLAPI extern
#  endif /* _STATIC_MESA support */
#  if defined(__MINGW32__) && defined(GL_NO_STDCALL) || defined(UNDER_CE)  /* The generated DLLs by MingW with STDCALL are not compatible with the ones done by Microsoft's compilers */
#    define GLAPIENTRY 
#  else
#    define GLAPIENTRY __stdcall
#  endif
#elif defined(__CYGWIN__) && defined(USE_OPENGL32) /* use native windows opengl32 */
#  define GLAPI extern
#  define GLAPIENTRY __stdcall
#elif defined(__OS2__) || defined(__EMX__) /* native os/2 opengl */
#  define GLAPI extern
#  define GLAPIENTRY _System
#  define APIENTRY _System
#  if defined(__GNUC__) && !defined(_System)
#    define _System
#  endif
#elif (defined(__GNUC__) && __GNUC__ >= 4) || (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590))
#  define GLAPI __attribute__((visibility("default")))
#  define GLAPIENTRY
#endif /* WIN32 && !CYGWIN */

/*
 * WINDOWS: Include windows.h here to define APIENTRY.
 * It is also useful when applications include this file by
 * including only glut.h, since glut.h depends on windows.h.
 * Applications needing to include windows.h with parms other
 * than "WIN32_LEAN_AND_MEAN" may include windows.h before
 * glut.h or gl.h.
 */
#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#ifndef NOMINMAX   /* don't define min() and max(). */
#define NOMINMAX
#endif
#include <windows.h>
#endif

#ifndef GLAPI
#define GLAPI extern
#endif

#ifndef GLAPIENTRY
#define GLAPIENTRY
#endif

#ifndef APIENTRY
#define APIENTRY GLAPIENTRY
#endif

/* "P" suffix to be used for a pointer to a function */
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifndef GLAPIENTRYP
#define GLAPIENTRYP GLAPIENTRY *
#endif

#if defined(PRAGMA_EXPORT_SUPPORTED)
#pragma export on
#endif

/*
 * End system-specific stuff.
 **********************************************************************/

#ifndef DONT_DEFINE_POINTERS_GL
#define OGL_PROC(ret,func,params) extern ret (APIENTRY *func) params;
#include "gl_es2_funcs.inl"
#include "gl_core_funcs.inl"
#undef OGL_PROC
#endif // DONT_DEFINE_POINTERS_GL

#endif // GL_INCLUDE_HPP
