#include "game_instance.hpp"

#include <utility>
#include <SDL_image.h>

#include "sdl_utility.hpp"
#include "drawing/enums.hpp"
#include "drawing/renderer.hpp"
#include "drawing/scene.hpp"
#include "drawing/colbuf.hpp"
#include "drawing/indbuf.hpp"
#include "drawing/vertbuf.hpp"
#include "drawing/uvbuf.hpp"
#include "drawing/mesh.hpp"
#include "drawing/texture.hpp"

static bool GetDisplayIndexFromWindow(SDL_Window* window, int* displayIndex)
{
	// NOTE: not checking number of displays because its assumed a display
	// exist if window creation succeeded.
	*displayIndex = SDL_GetWindowDisplayIndex(window);
	if(*displayIndex < 0)
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Unable to get display for current window: %s",
		            SDL_GetError());
		return false;
	}
	return true;
}

static Drawing::Texture TextureFromPath(Drawing::Renderer renderer,
                                        std::string_view path)
{
	using namespace Drawing;
	auto tex = renderer->NewTexture({TEXTURE_FILTERING_LINEAR, TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_REPEAT, 0, 0});
	SDL_Surface* image = IMG_Load(path.data());
	if((image != nullptr) &&
	   ((image = SDLU_SurfaceToRGBA32(image)) != nullptr))
	{
		tex->SetImage(image->w, image->h, image->pixels);
		SDL_FreeSurface(image);
	}
	return tex;
}

GameInstance::GameInstance(const Drawing::Backend backend) :
	SDLWindow(backend)
{
#ifndef __ANDROID__
	// Sets window to 80% size of the display it is currently in.
	auto SetWindowSize = [this]() -> bool
	{
		int displayIndex;
		SDL_Rect r;
		if(!GetDisplayIndexFromWindow(window, &displayIndex))
			return false;
		if(SDL_GetDisplayUsableBounds(displayIndex, &r) < 0)
		{
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
			            "Unable to get display usable bounds: %s",
			            SDL_GetError());
			return false;
		}
		int fWidth  = (r.w - r.x) * 4 / 5;
		int fHeight = (r.h - r.y) * 4 / 5;
		SDL_Log("Setting window size to (%i, %i)", fWidth, fHeight);
		SDL_SetWindowSize(window, fWidth, fHeight);
		return true;
	};
	if(!SetWindowSize())
	{
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
		            "Unable to set window size. Using default.");
		SDL_SetWindowSize(window, 1280, 720);
	}
#endif // #ifndef __ANDROID__
	// Clear renderer before showing window (avoids transparent window)
	renderer->DrawAllScenes();
	
	auto colBuf = renderer->NewColBuf(Drawing::BUFFER_HINT_STATIC);
	glm::vec4 test[3] =
	{
		{1.0f, 0.0f, 0.0f, 1.0f},
		{0.0f, 1.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f, 1.0f},
	};
	colBuf->Submit(test, 3);
	
	auto indBuf = renderer->NewIndBuf(Drawing::BUFFER_HINT_STATIC);
	short test2[3] =
	{
		0, 1, 2
	};
	indBuf->Submit(test2, 3);
	
	auto vertBuf = renderer->NewVertBuf(Drawing::BUFFER_HINT_STATIC);
	glm::vec3 test3[3] =
	{
		{-1.0f, -1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{1.0f, -1.0f, 0.0f},
	};
	vertBuf->Submit(test3, 3);
	
	auto uvBuf = renderer->NewUVBuf(Drawing::BUFFER_HINT_STATIC);
	glm::vec2 test4[3] =
	{
		{0.0f, 1.0f},
		{0.5f, 0.0f},
		{1.0f, 1.0f},
	};
	uvBuf->Submit(test4, 3);
	
	const Drawing::MeshCreateInfo mInfo =
	{
		Drawing::MESH_TOPOLOGY_TRIANGLE_LIST,
		true,
		false,
		vertBuf,
		indBuf,
		colBuf,
		uvBuf,
		TextureFromPath(renderer, "image.png"),
		false,
		{50.0f, 50.0f, 200.0f, 200.0f},
		glm::mat4(1.0f)
	};
	auto mesh = renderer->NewMesh(mInfo);
	
	const Drawing::SceneCreateInfo sInfo =
	{
		Drawing::SCENE_PROPERTY_NOTHING_BIT,
		{0.0f, 0.0f, 0.0f, 1.0f},
		0,
		glm::mat4(1.0f),
		glm::vec4(),
		nullptr
	};
	scene = renderer->NewScene2D(sInfo);
	scene->Insert(mesh);
	
	renderer->SetInitialScene(scene);
	
	// Set window title before showing window
	SDL_SetWindowTitle(window, "drawing2-test");
	SDL_ShowWindow(window);
	now = then = static_cast<unsigned>(SDL_GetTicks());
}

GameInstance::~GameInstance()
{}

void GameInstance::Run()
{
	SDL_Event e;
	while(!exiting)
	{
		while(SDL_PollEvent(&e) != 0)
			OnEvent(e);
		Tick();
		renderer->DrawAllScenes();
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
		SDL_GL_GetDrawableSize(window, &width, &height);
		SDL_Log("Resized to (%i, %i)", width, height);
		scene->SetViewport({0, 0, width, height});
	}
	
	// event stuff here
}

void GameInstance::Tick()
{
	if(recording != 0u)
		now += 1000u / recording;
	else
		now = static_cast<unsigned>(SDL_GetTicks());
	elapsed = static_cast<float>(now - then) * 0.001f;
	// tick stuff here
	then = now;
}
