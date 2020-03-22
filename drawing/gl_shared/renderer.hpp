#ifndef DRAWING_GL_SHARED_RENDERER_HPP
#define DRAWING_GL_SHARED_RENDERER_HPP
#include "shaders_container.hpp"
#include "../renderer.hpp"

struct SDL_Window;

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class Renderer : public IRenderer
{
public:
	std::shared_ptr<ShadersContainer> sc;
	
	Renderer(SDL_Window* sdlWindow);
	
	bool SetVSync(VSyncState vsync) override;
	SVertBuf NewVertBuf(BufferHint hint) override;
	SIndBuf NewIndBuf(BufferHint hint) override;
	SColBuf NewColBuf(BufferHint hint) override;
	SUVBuf NewUVBuf(BufferHint hint) override;
	STexture NewTexture(const TextureCreateInfo& info) override;
protected:
	SDL_Window* sdlWindow{nullptr};
};

} // GLShared

} // Detail

} // Drawing

#endif // DRAWING_GL_SHARED_RENDERER_HPP
