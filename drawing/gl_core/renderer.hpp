#ifndef DRAWING_GL_CORE_RENDERER_HPP
#define DRAWING_GL_CORE_RENDERER_HPP
#include "../gl_shared/renderer.hpp"

namespace Drawing
{

namespace GLCore
{

class Renderer final : public GLShared::Renderer
{
public:
	Renderer(SDL_Window* sdlWindow);
	virtual ~Renderer() = default;
	
	// IRenderer overrides
	SScene NewScene2D(const SceneCreateInfo& info) override;
	SScene NewScene3D(const SceneCreateInfo& info) override;
	SMesh NewMesh(const MeshCreateInfo& info) override;
	
	// GLShared::Renderer overrides
	void BlitToWindowFramebuffer(const GLShared::Scene& scene) override;
};

} // namespace GLCore

} // namespace Drawing

#endif // DRAWING_GL_CORE_RENDERER_HPP
