#ifndef EGO_GL_CORE_RENDERER_HPP
#define EGO_GL_CORE_RENDERER_HPP
#include "../gl_shared/renderer.hpp"

namespace Ego::GLCore
{

class Renderer final : public GLShared::Renderer
{
public:
	Renderer();
	virtual ~Renderer() = default;
	
	// IRenderer overrides
	SScene NewScene2D(const SceneCreateInfo& info) override;
	SScene NewScene3D(const SceneCreateInfo& info) override;
	SMesh NewMesh(const MeshCreateInfo& info) override;
	
	// GLShared::Renderer overrides
	void BlitToWindowFramebuffer(const GLShared::Scene& scene) override;
};

} // namespace Ego::GLCore

#endif // EGO_GL_CORE_RENDERER_HPP
