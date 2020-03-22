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
	
	Drawing::Scene NewScene2D(const SceneCreateInfo& info) override;
	Drawing::Scene NewScene3D(const SceneCreateInfo& info) override;
	Drawing::Mesh NewMesh(const MeshCreateInfo& info) override;
	
	void SetInitialScene(Drawing::Scene scene) override;
	Drawing::Scene GetInitialScene() override;
	
	void DrawAllScenes() override;
private:
	GLShared::Program prog;
	std::shared_ptr<Scene> initialScene;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_RENDERER_HPP
