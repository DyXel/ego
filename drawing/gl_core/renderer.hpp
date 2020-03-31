#ifndef DRAWING_GL_CORE_RENDERER_HPP
#define DRAWING_GL_CORE_RENDERER_HPP
#include "../gl_shared/renderer.hpp"

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
	virtual ~Renderer();
	
	// Drawing::IRenderer overrides
	SScene NewScene2D(const SceneCreateInfo& info) override;
	SScene NewScene3D(const SceneCreateInfo& info) override;
	SMesh NewMesh(const MeshCreateInfo& info) override;
	
	// GLShared::Renderer overrides
	void BlitToWindowFramebuffer(const GLShared::Rect& viewport, GLuint to) override;
private:
	GLuint spo; // Shader Program Object used to blit framebuffer
	GLuint mvpUniLoc;
	GLuint vao;
};

} // namespace GLCore

} // namespace Detail

} // namespace Drawing

#endif // DRAWING_GL_CORE_RENDERER_HPP
