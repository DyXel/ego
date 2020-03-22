#include "renderer.hpp"

#include <exception>
#include <SDL.h>

#include "mesh.hpp"
#include "scene.hpp"
#include "scene2d.hpp"
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

Drawing::Scene Renderer::NewScene2D(const SceneCreateInfo& info)
{
	return std::make_shared<Scene2D>(sc, info);
}

Drawing::Scene Renderer::NewScene3D(const SceneCreateInfo& info)
{
	throw std::exception();
}

Drawing::Mesh Renderer::NewMesh(const MeshCreateInfo& info)
{
	return std::make_shared<Mesh>(info);
}

void Renderer::SetInitialScene(Drawing::Scene scene)
{
	initialScene = std::dynamic_pointer_cast<Scene>(scene);
}

Drawing::Scene Renderer::GetInitialScene()
{
	throw std::exception();
}

void Renderer::DrawAllScenes()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if(initialScene == nullptr)
	{
		SDL_GL_SwapWindow(sdlWindow);
		return;
	}
	
	Scene* currScene = initialScene.get();
	do
	{
		currScene->Draw();
		currScene = currScene->GetNext();
	}while(currScene != nullptr);
	
	SDL_GL_SwapWindow(sdlWindow);
}

} // GLCore

} // Detail

} // Drawing
