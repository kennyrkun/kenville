#include "MainMenuState.hpp"
#include "GameCreationState.hpp"

void MainMenuState::Init(AppEngine* app_)
{
	std::cout << "Initialising MainMenuState" << std::endl;

	app = app_;

	font.loadFromFile(app->settings.workDir + "resources/fonts/Arial.ttf");

	bobwars.setFont(font);
	bobwars.setString("bobwars");
	bobwars.setCharacterSize(56);

	sf::Texture* backgroundMediaTexture = nullptr;

	if (backgroundMediaTexture)
	{
		backgroundMediaTexture->setSmooth(true);
		backgroundmedia.setSize(sf::Vector2f(app->window.getSize().y, app->window.getSize().y));
		backgroundmedia.setTexture(backgroundMediaTexture);

		//logoTexture.setSmooth(true);
		backgroundmedia.setOrigin(backgroundmedia.getLocalBounds().width, 0);
		backgroundmedia.setPosition(sf::Vector2f(app->window.getSize().x, 0));
	}
	else
	{
		std::cerr << "Failed to load title screen logo." << std::endl;
	}

	menu = new SFUI::Menu(app->window);
	menu->addButton("New Game", MAIN_MENU_CALLBACKS::PLAY_BUTTON);
	menu->addButton("Load", MAIN_MENU_CALLBACKS::LOAD_BUTTON);
	menu->addButton("Settings", MAIN_MENU_CALLBACKS::SETTINGS_BUTTON);
	menu->addButton("Exit", MAIN_MENU_CALLBACKS::EXIT_BUTTON);

	menu->setPosition(sf::Vector2f((app->window.getSize().x / 2 - (menu->getSize().x / 2)) / 4, app->window.getSize().y / 2 - (menu->getSize().y / 2)));

	bobwars.setPosition(menu->getPosition() - sf::Vector2f(50, bobwars.getLocalBounds().width / 2));
	
	std::cout << "MainMenuState ready." << std::endl;
}

void MainMenuState::Cleanup()
{
	std::cout << "Cleaning up MainMenuState." << std::endl;

	delete menu;

	std::cout << "Cleaned up MainMenuState." << std::endl;
}

void MainMenuState::Pause()
{
	std::cout << "MainMenuState paused." << std::endl;
}

void MainMenuState::Resume()
{
	std::cout << "MainMenuState resumed." << std::endl;
}

void MainMenuState::HandleEvents()
{
	sf::Event event;
	while (app->window.pollEvent(event))
	{
		int id = menu->onEvent(event);
		switch (id)
		{
		case MAIN_MENU_CALLBACKS::PLAY_BUTTON:
			std::cout << "Starting a new game..." << std::endl;
			app->ChangeState(new GameCreationState);
			return;
		case MAIN_MENU_CALLBACKS::LOAD_BUTTON:
			std::cerr << "Saving/Loading system not yet implemented." << std::endl;
			break;
		case MAIN_MENU_CALLBACKS::SETTINGS_BUTTON:
			std::cerr << "Settings system not yet implemented."  << std::endl;
			break;
		case MAIN_MENU_CALLBACKS::EXIT_BUTTON:
			std::cout << "Exiting game.." << std::endl;
			app->Quit();
			return;
		default:
			break;
		}

		if (event.type == sf::Event::EventType::Closed)
		{
			app->Quit();
			return;		
		}
		else if (event.type == sf::Event::EventType::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Key::Tilde)
			{
				app->settings.debug = !app->settings.debug;

				std::cout << "cl_debug set to " + std::to_string(app->settings.debug) << std::endl;
			}
		}
	}
}

void MainMenuState::Update()
{
	r += dr;
	g += dg;
	b += db;

	if (r == 255 && g == 0 && b == 0)
		dr = 0; dg = 1; db = 0;

	if (r == 255 && g == 255 && b == 0)
		dr = -1; dg = 0; db = 0;

	if (r == 0 && g == 255 && b == 0)
		dr = 0; dg = 0; db = 1;

	if (r == 0 && g == 255 && b == 255)
		dr = 0; dg = -1; db = 0;

	if (r == 0 && g == 0 && b == 255)
		dr = 1; dg = 0; db = 0;

	if (r == 255 && g == 0 && b == 255)
		dr = 0; dg = 0; db = -1;
}

void MainMenuState::Draw()
{
	app->window.clear(sf::Color(64, 64, 64));

	app->window.draw(backgroundmedia);

	app->window.draw(bobwars);

	app->window.draw(*menu);

	app->window.display();
}

bool MainMenuState::mouseIsOver(sf::Shape &object)
{
	if (object.getGlobalBounds().contains(app->window.mapPixelToCoords(sf::Mouse::getPosition(app->window))))
		return true;
	else
		return false;
}
