#ifndef EGO_GL_ES_RENDERER_HPP
#define EGO_GL_ES_RENDERER_HPP
#include "../gl_shared/renderer.hpp"

namespace Ego::GLES
{

class Renderer final : public GLShared::Renderer
{
public:
	Renderer();
	
	// IRenderer overrides
	SScene NewScene2D(const SceneCreateInfo& info) override;
	SScene NewScene3D(const SceneCreateInfo& info) override;
	SMesh NewMesh(const MeshCreateInfo& info) override;
	
	// GLShared::Renderer overrides
	void BlitToWindowFramebuffer(const GLShared::Scene& scene) override;
private:
	GLShared::Program prog; // GL Program used to blit to window framebuffer
};

} // namespace Ego::GLES

#endif // EGO_GL_ES_RENDERER_HPP
