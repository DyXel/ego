#include "game_instance.hpp"

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

static Drawing::STexture TextureFromPath(Drawing::IRenderer& renderer,
                                        std::string_view path)
{
	using namespace Drawing;
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
	const glm::mat4 proj = glm::perspective(fov, ar, 0.1f, 20.0f);
	const glm::vec3 pos = {0.0f, 0.1f, 8.0f};
	const glm::vec3 to = {0.0f, 0.0f, 0.0f};
	const glm::vec3 up = {0.0f, 0.0f, 1.0f};
	const glm::mat4 view = glm::lookAt(pos, to, up);
	return proj * view;
}

GameInstance::GameInstance(const Drawing::Backend backend) :
	SDLWindow(backend)
{
	constexpr int WINDOW_WIDTH  = 800;
	constexpr int WINDOW_HEIGHT = 800;
	SDL_SetWindowSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	// Set up 3d scene
	const Drawing::SceneCreateInfo sInfo =
	{
		Drawing::SCENE_PROPERTY_CLEAR_COLOR_BUFFER_BIT |
		Drawing::SCENE_PROPERTY_CLEAR_DEPTH_BUFFER_BIT |
		Drawing::SCENE_PROPERTY_ENABLE_DEPTH_TEST_BIT,
		{0.4f, 0.4f, 0.4f, 1.0f},
		CreateViewProjMat4(WINDOW_WIDTH, WINDOW_HEIGHT, glm::pi<float>() / 2.0f),
		glm::vec4({0, 0, WINDOW_WIDTH, WINDOW_HEIGHT}),
		nullptr
	};
	scene = renderer->NewScene3D(sInfo);
	renderer->SetInitialScene(scene);
	
	Drawing::MeshCreateInfo mInfo =
	{
		Drawing::MESH_TOPOLOGY_TRIANGLE_STRIP,
		true,
		true,
		renderer->QuadVertBuf(),
		renderer->QuadIndBuf(),
		nullptr,
		renderer->QuadUVBuf(),
		TextureFromPath(*renderer, "eye.png"),
		nullptr,
		glm::mat4(1.0f),
	};
	for(std::size_t i = 0; i < alphaMeshes.size(); i++)
	{
		auto mesh = renderer->NewMesh(mInfo);
		scene->Insert(mesh);
		alphaMeshes[i] = mesh.get();
	}
	mInfo.transparent = false;
	mInfo.diffuse = TextureFromPath(*renderer, "zone.png");
	for(std::size_t i = 0; i < solidMeshes.size(); i++)
	{
		auto mesh = renderer->NewMesh(mInfo);
		scene->Insert(mesh);
		solidMeshes[i] = mesh.get();
	}
	
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
	rotation += elapsed;
	RefreshMeshes();
	then = now;
}

void GameInstance::RefreshMeshes()
{
	static const glm::vec3 rot1 = {-0.5f, 1.0f, 0.0f};
	static const glm::mat4 trans1 = glm::translate(glm::vec3{0.0f, 0.0f, 4.0f});
	static const glm::vec3 rot2 = {0.5f, 0.4f, 0.0f};
	static const glm::mat4 trans2 = glm::translate(glm::vec3{0.0f, 0.0f, -2.0f});
	for(std::size_t i = 0; i < alphaMeshes.size(); i++)
	{
		float angle = i * ((glm::pi<float>() * 2.0f) / alphaMeshes.size()) + rotation;
		auto rotMat = glm::rotate(angle, rot1);
		alphaMeshes[i]->SetModelMat4(rotMat * trans1);
	}
	for(std::size_t i = 0; i < solidMeshes.size(); i++)
	{
		float angle = i * ((glm::pi<float>() * 2.0f) / solidMeshes.size()) + rotation;
		auto rotMat = glm::rotate(angle, rot2);
		solidMeshes[i]->SetModelMat4(rotMat * trans2);
	}
}
