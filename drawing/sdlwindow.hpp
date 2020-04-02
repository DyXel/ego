#ifndef EGO_SDLWINDOW_HPP
#define EGO_SDLWINDOW_HPP
#include <memory>
#include <vector>
#include <SDL.h>

#include "ego_fwd.hpp"

namespace Ego
{

// Available Backends
enum Backend
{
	NOT_LOADED = 0,  // Used to check if any backend has been loaded yet
	OPENGL_CORE, // OpenGL 4.1+
	OPENGL_ES    // OpenGL ES 2.0+
};

class SDLWindow
{
public:
	SDLWindow(const Backend backend);
	~SDLWindow();
	SRenderer renderer;
protected:
	SDL_Window* window;
private:
	SDL_GLContext glCtx;
	
	bool GLCreateContext();
	bool LoadGLCore();
	bool LoadGLES();
};

} // Drawing

#endif // EGO_SDLWINDOW_HPP
