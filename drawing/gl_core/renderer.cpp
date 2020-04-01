#include "renderer.hpp"

#include <exception>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr, glm::identity

#include "mesh.hpp"
#include "scene2d.hpp"
#include "scene3d.hpp"
#include "../gl_shared/gl_include.hpp"
#include "../gl_shared/shader.hpp"
#include "../gl_shared/program.hpp"

namespace Drawing
{

namespace GLCore
{

Renderer::Renderer(SDL_Window* sdlWindow) : GLShared::Renderer(sdlWindow)
{}

SScene Renderer::NewScene2D(const SceneCreateInfo& info)
{
	return std::make_shared<Scene2D>(cache, *this, info);
}

SScene Renderer::NewScene3D(const SceneCreateInfo& info)
{
	return std::make_shared<Scene3D>(cache, *this, info);
}

SMesh Renderer::NewMesh(const MeshCreateInfo& info)
{
	return std::make_shared<Mesh>(info);
}

void Renderer::BlitToWindowFramebuffer(const GLShared::Scene& scene)
{
	using namespace GLShared;
	const auto& vp = scene.Viewport();
	glBindFramebuffer(GL_READ_FRAMEBUFFER, scene.FramebufferObject());
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBlitFramebuffer(0, 0, vp.z, vp.w,
	                  vp.x, vp.y, vp.z, vp.w,
	                  GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

} // GLCore

} // Drawing
