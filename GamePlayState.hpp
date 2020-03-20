#ifndef GAME_HPP
#define GAME_HPP

#include "AppEngine.hpp"
#include "AppState.hpp"

#include "EntityManager.hpp"
#include "PlayerCharacter.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>	

struct GameWorld
{
	void loadMapFile(std::string file);

	sf::Texture mapTexture;
	sf::RectangleShape map;

	size_t mapSizeX;
	size_t mapSizeY;
};

class GamePlayState : public AppState
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
	AppEngine* app = nullptr;

	void updateGameCamera();

	EntityManager entman;

	PlayerCharacter* playerCharacter;

	sf::Time timePerFrame; // 60 frames per second
	sf::Time timeSinceLastUpdate;

	sf::RectangleShape world;
	sf::Texture		   *worldTexture = nullptr;

	sf::View* mainView2 = nullptr;
	sf::View* viewAnchor = nullptr;

	sf::Clock deltaClock;  // tracks how much time has past since the last frame
	sf::Clock framesClock; // for maxfps
	sf::Clock gameClock; // total time of the game
};

#endif /* GAME_HPP */
