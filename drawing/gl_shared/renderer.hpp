#ifndef DRAWING_GL_SHARED_RENDERER_HPP
#define DRAWING_GL_SHARED_RENDERER_HPP
#include "program_provider.hpp"
#include "../renderer.hpp"

struct SDL_Window;

namespace Drawing
{

namespace Detail
{

namespace GLShared
{

class Scene;

class Renderer : public IProgramProvider, public IRenderer
{
public:
	Renderer(SDL_Window* sdlWindow);
	
	// GLShared::IProgramProvider overrides
	const Program& GetProgram(ProgramTypes value) const override;
	
	// Drawing::IRenderer overrides
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
	std::array<Program, PROGRAM_TYPES_COUNT> programs;
};

} // GLShared

} // Detail

} // Drawing

#endif // DRAWING_GL_SHARED_RENDERER_HPP
