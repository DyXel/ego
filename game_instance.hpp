#ifndef GAME_INSTANCE_HPP
#define GAME_INSTANCE_HPP
#include <memory>
#include <SDL.h>
#include "drawing/sdlwindow.hpp"

class GameInstance : public Ego::SDLWindow
{
public:
	GameInstance(const Ego::Backend backend);
	~GameInstance();
	
	GameInstance(const GameInstance&) = delete;
	GameInstance(GameInstance&&) = delete;
	GameInstance& operator=(const GameInstance&) = delete;
	GameInstance& operator=(GameInstance&&) = delete;
	
	void Run();
private:
	bool exiting{false};
	
	int width{}, height{};
	
	unsigned now, then;
	unsigned recording{0u}; // if non 0. Framerate being recorded at.
	float elapsed{};
	
	float rotation{0u};
	Ego::SScene scene;
	std::array<Ego::IMesh*, 8> alphaMeshes{};
	std::array<Ego::IMesh*, 8> solidMeshes{};
	
	void OnEvent(const SDL_Event& e);
	void Tick();
	
	void RefreshMeshes();
};

#endif // GAME_INSTANCE_HPP
