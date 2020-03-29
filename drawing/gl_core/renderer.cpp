#include "renderer.hpp"

#include <exception>
#include <SDL.h>

#include "mesh.hpp"
#include "scene2d.hpp"
#include "scene3d.hpp"
#include "../gl_shared/gl_include.hpp"
#include "../gl_shared/shader.hpp"
#include "../gl_shared/program.hpp"

namespace Drawing
{

namespace Detail
{

namespace GLCore
{

Renderer::Renderer(SDL_Window* sdlWindow) : GLShared::Renderer(sdlWindow)
{}

SScene Renderer::NewScene2D(const SceneCreateInfo& info)
{
	return std::make_shared<Scene2D>(*this, info);
}

SScene Renderer::NewScene3D(const SceneCreateInfo& info)
{
	return std::make_shared<Scene3D>(*this, info);
}

SMesh Renderer::NewMesh(const MeshCreateInfo& info)
{
	return std::make_shared<Mesh>(info);
}

} // GLCore

} // Detail

} // Drawing
