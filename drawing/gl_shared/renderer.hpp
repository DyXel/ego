#ifndef DRAWING_GL_SHARED_RENDERER_HPP
#define DRAWING_GL_SHARED_RENDERER_HPP
#include "../renderer.hpp"

struct SDL_Window;

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class Scene;
class ShadersContainer;

class Renderer : public IRenderer
{
public:
	Renderer(SDL_Window* sdlWindow);
	
	bool SetVSync(VSyncState vsync) override;
	
	SVertBuf NewVertBuf(BufferHint hint) override;
	SIndBuf NewIndBuf(BufferHint hint) override;
	SColBuf NewColBuf(BufferHint hint) override;
	SUVBuf NewUVBuf(BufferHint hint) override;
	STexture NewTexture(const TextureCreateInfo& info) override;
	
	void SetInitialScene(SScene scene) override;
	SScene GetInitialScene() override;
	
	void DrawAllScenes() override;
protected:
	SDL_Window* sdlWindow;
	std::shared_ptr<Scene> initialScene;
	std::shared_ptr<ShadersContainer> sc;
};

} // GLShared

} // Detail

} // Drawing

#endif // DRAWING_GL_SHARED_RENDERER_HPP
