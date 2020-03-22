#ifndef DRAWING_GL_CORE_RENDERER_HPP
#define DRAWING_GL_CORE_RENDERER_HPP
#include "scene.hpp"
#include "../gl_shared/renderer.hpp"
#include "../gl_shared/program.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

class Renderer final : public GLShared::Renderer
{
public:
	Renderer(SDL_Window* sdlWindow);
	
	SScene NewScene2D(const SceneCreateInfo& info) override;
	SScene NewScene3D(const SceneCreateInfo& info) override;
	SMesh NewMesh(const MeshCreateInfo& info) override;
	
	void SetInitialScene(SScene scene) override;
	SScene GetInitialScene() override;
	
	void DrawAllScenes() override;
private:
	GLShared::Program prog;
	std::shared_ptr<Scene> initialScene;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_RENDERER_HPP
