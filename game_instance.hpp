#ifndef GAME_INSTANCE_HPP
#define GAME_INSTANCE_HPP
#include <memory>
#include <SDL.h>

#include "drawing/ego_fwd.hpp"

class GameInstance
{
public:
	GameInstance();
	~GameInstance();
	
	GameInstance(const GameInstance&) = delete;
	GameInstance(GameInstance&&) = delete;
	GameInstance& operator=(const GameInstance&) = delete;
	GameInstance& operator=(GameInstance&&) = delete;
	
	void Run();
private:
	SDL_Window* sdlWindow;
	SDL_GLContext sdlGLCtx;
	
	int width, height;
	bool exiting{false};
	
	unsigned now, then;
	unsigned recording{0u}; // if non 0. Framerate being recorded at.
	float elapsed{};
	
	float rotation{0u};
	Ego::SRenderer renderer;
	Ego::SScene scene;
	std::array<Ego::IMesh*, 8> alphaMeshes{};
	std::array<Ego::IMesh*, 8> solidMeshes{};
	
	void OnEvent(const SDL_Event& e);
	void Tick();
	
	void RefreshMeshes();
};

#endif // GAME_INSTANCE_HPP
