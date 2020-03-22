#ifndef GAME_INSTANCE_HPP
#define GAME_INSTANCE_HPP
#include <memory>
#include <SDL.h>
#include "drawing/sdlwindow.hpp"

#include "drawing/scene_fwd.hpp"

class GameInstance : public Drawing::SDLWindow
{
public:
	GameInstance(const Drawing::Backend backend);
	~GameInstance();
	
	GameInstance(const GameInstance&) = delete;
	GameInstance(GameInstance&&) = delete;
	GameInstance& operator=(const GameInstance&) = delete;
	GameInstance& operator=(GameInstance&&) = delete;
	
	void Run();
private:
	bool exiting{false};
	
	int width, height;
	
	unsigned now, then;
	unsigned recording{0u}; // if non 0. Framerate being recorded at.
	float elapsed{};
	
	Drawing::Scene scene;
	
	void OnEvent(const SDL_Event& e);
	void Tick();
};

#endif // GAME_INSTANCE_HPP
