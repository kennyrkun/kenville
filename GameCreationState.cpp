#include "GameCreationState.hpp"

#include "AppEngine.hpp"
#include "AppState.hpp"

#include "GamePlayState.hpp"

#include <iostream>

void GameCreationState::Init(AppEngine* app_)
{
	std::cout << "GameCreationState Init" << std::endl;

	app = app_;

	std::cout << "GameCreationState ready." << std::endl;
}

void GameCreationState::Cleanup()
{
	std::cout << "Cleaning up GameCreationState." << std::endl;

	std::cout << "Cleaned up GameCreationState." << std::endl;
}

void GameCreationState::Pause()
{
	std::cout << "GameCreationState paused." << std::endl;
}

void GameCreationState::Resume()
{
	std::cout << "GameCreationState resumed." << std::endl;
}

void GameCreationState::HandleEvents()
{
}

void GameCreationState::Update()
{
	app->ChangeState(new GamePlayState);
	return;
}

void GameCreationState::Draw()
{
}

