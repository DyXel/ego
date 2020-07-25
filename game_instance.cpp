#include "game_instance.hpp"

#include <string>
#include <stdexcept>
#include <utility>
#include <SDL_image.h>
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/matrix_transform.hpp> // glm::lookAt
#include <glm/gtx/transform.hpp> // glm::scale

#include "sdl_utility.hpp"
#include "drawing/enums.hpp"
#include "drawing/renderer.hpp"
#include "drawing/scene.hpp"
#include "drawing/mesh.hpp"
#include "drawing/texture.hpp"

#define USE_GL_CORE

constexpr int DEFAULT_WINDOW_WIDTH  = 800;
constexpr int DEFAULT_WINDOW_HEIGHT = 800;

static Ego::STexture TextureFromPath(
	Ego::IRenderer& renderer,
	std::string_view path)
{
	using namespace Ego;
	auto tex = renderer.NewTexture({TEXTURE_FILTERING_LINEAR, TEXTURE_WRAP_REPEAT,
	                               TEXTURE_WRAP_REPEAT, 0, 0, nullptr});
	SDL_Surface* image = IMG_Load(path.data());
	if((image != nullptr) &&
	   ((image = SDLU_SurfaceToRGBA32(image)) != nullptr))
	{
		tex->SetImage(image->w, image->h, image->pixels);
		SDL_FreeSurface(image);
	}
	return tex;
}

glm::mat4 CreateViewProjMat4(int width, int height, float fov)
{
	const auto ar = static_cast<float>(width) / height;
	const glm::mat4 proj = glm::perspective(fov, ar, 0.1F, 20.0F);
	const glm::vec3 pos = {0.0F, 0.1F, 8.0F};
	const glm::vec3 to = {0.0F, 0.0F, 0.0F};
	const glm::vec3 up = {0.0F, 0.0F, 1.0F};
	const glm::mat4 view = glm::lookAt(pos, to, up);
	return proj * view;
}

GameInstance::GameInstance() :
	width(DEFAULT_WINDOW_WIDTH),
	height(DEFAULT_WINDOW_HEIGHT)
{
	//*** SDL GL AND RENDERER INITIALIZATION ***//
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
// 	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
	// Don't use deprecated functionality. Required on MacOS
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
	// Configure SDL to create the context we want
#ifdef USE_GL_CORE
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#else
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
#endif // USE_GL_CORE
	// Create window
	sdlWindow = SDL_CreateWindow("drawing2-test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if(sdlWindow == nullptr)
	{
		std::string errStr("Unable to create SDL Window: ");
		errStr += SDL_GetError();
		throw std::runtime_error(errStr);
	}
	// Create GL context
	sdlGLCtx = SDL_GL_CreateContext(sdlWindow);
	if(sdlGLCtx == nullptr)
	{
		std::string errStr("Unable to create GL Context: ");
		errStr += SDL_GetError();
		SDL_DestroyWindow(sdlWindow);
		throw std::runtime_error(errStr);
	}
	// Enable vsync
	SDL_GL_SetSwapInterval(1);
	// Create Ego Renderer
#ifdef USE_GL_CORE
	renderer = Ego::MakeGLCoreRenderer([](const char* procName){return SDL_GL_GetProcAddress(procName);});
#else
	renderer = Ego::MakeGLESRenderer(SDL_GL_GetProcAddress);
#endif // USE_GL_CORE
	//*** ACTUAL EGO CODE ***//
	// Set up 3d scene
	const Ego::SceneCreateInfo sInfo =
	{
		Ego::SCENE_PROPERTY_CLEAR_COLOR_BUFFER_BIT |
		Ego::SCENE_PROPERTY_CLEAR_DEPTH_BUFFER_BIT |
		Ego::SCENE_PROPERTY_ENABLE_DEPTH_TEST_BIT,
		{0.4F, 0.4F, 0.4F, 1.0F},
		CreateViewProjMat4(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, glm::pi<float>() / 2.0F),
		glm::vec4({0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT}),
		nullptr
	};
	scene = renderer->NewScene3D(sInfo);
	renderer->SetInitialScene(scene);
	
	// Set up meshes
	Ego::MeshCreateInfo mInfo =
	{
		renderer->QuadTopology(),
		true,
		true,
		renderer->QuadVertBuf(),
		renderer->QuadIndBuf(),
		nullptr,
		renderer->QuadUVBuf(),
		TextureFromPath(*renderer, "eye.png"),
		nullptr,
		glm::mat4(1.0F),
	};
	for(auto& alphaMesh : alphaMeshes)
	{
		auto mesh = renderer->NewMesh(mInfo);
		scene->Insert(mesh);
		alphaMesh = mesh.get();
	}
	mInfo.transparent = false;
	mInfo.diffuse = TextureFromPath(*renderer, "zone.png");
	for(auto& solidMesh : solidMeshes)
	{
		auto mesh = renderer->NewMesh(mInfo);
		scene->Insert(mesh);
		solidMesh = mesh.get();
	}
	
	// Set window title before showing window
	now = then = static_cast<unsigned>(SDL_GetTicks());
}

GameInstance::~GameInstance()
{
	renderer.reset();
	SDL_GL_DeleteContext(sdlGLCtx);
	SDL_DestroyWindow(sdlWindow);
}

void GameInstance::Run()
{
	SDL_Event e;
	while(!exiting)
	{
		while(SDL_PollEvent(&e) != 0)
			OnEvent(e);
		Tick();
		renderer->DrawAllScenes();
		SDL_GL_SwapWindow(sdlWindow);
	}
}

void GameInstance::OnEvent(const SDL_Event& e)
{
	const auto eType = e.type;
	if(eType == SDL_QUIT)
		exiting = true;
	// If the event is a window size change event update the viewport/extent
	// to match the new size, also, save the new size.
	if(eType == SDL_WINDOWEVENT &&
	   e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		SDL_GL_GetDrawableSize(sdlWindow, &width, &height);
		SDL_Log("Resized to (%i, %i)", width, height);
		scene->SetViewport({0, 0, width, height});
	}
	// event stuff here
}

void GameInstance::Tick()
{
	if(recording != 0U)
		now += 1000U / recording;
	else
		now = static_cast<unsigned>(SDL_GetTicks());
	elapsed = static_cast<float>(now - then) * 0.001F;
	rotation += elapsed;
	RefreshMeshes();
	then = now;
}

void GameInstance::RefreshMeshes()
{
	static const glm::vec3 rot1 = {-0.5F, 1.0F, 0.0F};
	static const glm::mat4 trans1 = glm::translate(glm::vec3{0.0F, 0.0F, 4.0F});
	static const glm::vec3 rot2 = {0.5F, 0.4F, 0.0F};
	static const glm::mat4 trans2 = glm::translate(glm::vec3{0.0F, 0.0F, -2.0F});
	for(std::size_t i = 0; i < alphaMeshes.size(); i++)
	{
		float angle = i * ((glm::pi<float>() * 2.0F) / alphaMeshes.size()) + rotation;
		auto rotMat = glm::rotate(angle, rot1);
		alphaMeshes[i]->SetModelMat4(rotMat * trans1);
	}
	for(std::size_t i = 0; i < solidMeshes.size(); i++)
	{
		float angle = i * ((glm::pi<float>() * 2.0F) / solidMeshes.size()) + rotation;
		auto rotMat = glm::rotate(angle, rot2);
		solidMeshes[i]->SetModelMat4(rotMat * trans2);
	}
}
