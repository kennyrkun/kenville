#ifndef GAME_CREATION_STATE_HPP
#define GAME_CREATION_STATE_HPP

#include "AppState.hpp"

class GameCreationState : public AppState
{
public:
	void Init(AppEngine* app_);
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents();
	void Update();
	void Draw();

private:
	AppEngine* app;
};

#endif // !GAME_CREATION_STATE_HPP
