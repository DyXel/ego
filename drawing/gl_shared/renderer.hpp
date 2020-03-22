#ifndef DRAWING_GL_SHARED_RENDERER_HPP
#define DRAWING_GL_SHARED_RENDERER_HPP
#include "../renderer.hpp"

#include "shaders_container.hpp"

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
	Drawing::VertBuf NewVertBuf(BufferHint hint) override;
	Drawing::IndBuf NewIndBuf(BufferHint hint) override;
	Drawing::ColBuf NewColBuf(BufferHint hint) override;
	Drawing::UVBuf NewUVBuf(BufferHint hint) override;
	Drawing::Texture NewTexture(const TextureCreateInfo& info) override;
protected:
	SDL_Window* sdlWindow{nullptr};
};

} // GLShared

} // Detail

} // Drawing

#endif // DRAWING_GL_SHARED_RENDERER_HPP
