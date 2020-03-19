#include "AppEngine.hpp"
#include "AppState.hpp"

#include <SFUI/Theme.hpp>

#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

// INFO: keep this bare minimums
// AppEngine is the core of the application,
// and should rely on as little external
// resources as reasonably possible.

AppEngine::AppEngine()
{
	std::cout << "appengine constructed" << std::endl;
}

void AppEngine::Init(AppSettings settings_)
{
	std::cout << "AppEngine Init" << std::endl;

	settings = settings_;

	for (size_t i = 0; i < settings.launchOptions.argc; i++)
	{
		std::cout << i << ": " << settings.launchOptions.argv[i] << std::endl;

		if (std::string(settings.launchOptions.argv[i]) == "-serverIp")
		{
			settings.server.serverIpAddress = settings.launchOptions.argv[i + 1];
			std::cout << "set server ip to " << settings.server.serverIpAddress << std::endl;
		}

		if (std::string(settings.launchOptions.argv[i]) == "-serverPort")
		{
			settings.server.serverPort = std::stoi(settings.launchOptions.argv[i + 1]);
			std::cout << "set server ip to " << settings.server.serverIpAddress << std::endl;
		}
	}

	for (int i = 0; i < settings.launchOptions.argc; i++)
	{
		if (std::string(settings.launchOptions.argv[i]) == "-vsync")
			settings.graphics.vsync = true;

		if (std::string(settings.launchOptions.argv[i]) == "-maxfps")
			// next arg should be an int (the maxfps)
			settings.graphics.maxfps = std::stoi(settings.launchOptions.argv[i += 1]);
	}

	window.create(sf::VideoMode(settings.graphics.width, settings.graphics.height), settings.title);

	if (!fs::exists(settings.workDir))
	{
		fs::create_directory(settings.workDir);
		fs::create_directory(settings.workDir + "resource");
		fs::create_directory(settings.workDir + "resource/textures");
		fs::create_directory(settings.workDir + "resource/fonts");
	}

	SFUI::Theme::loadFont(settings.workDir + "resources/fonts/Arial.ttf");
	SFUI::Theme::loadTexture(settings.workDir + "resources/textures/square.png");

	SFUI::Theme::textCharacterSize = 11;
	SFUI::Theme::click.textColor = SFUI::Theme::hexToRgb("#191B18");
	SFUI::Theme::click.textColorHover = SFUI::Theme::hexToRgb("#191B18");
	SFUI::Theme::click.textColorFocus = SFUI::Theme::hexToRgb("#000000");
	SFUI::Theme::input.textColor = SFUI::Theme::hexToRgb("#000000");
	SFUI::Theme::input.textColorHover = SFUI::Theme::hexToRgb("#CC7A00");
	SFUI::Theme::input.textColorFocus = SFUI::Theme::hexToRgb("#000000");
	SFUI::Theme::windowBgColor = SFUI::Theme::hexToRgb("#dddbde");
	SFUI::Theme::PADDING = 2.f;

	running = true;

	std::cout << "AppEngine ready" << std::endl;
}

void AppEngine::Cleanup()
{
	std::cout << "Cleaning up AppEngine." << std::endl;
	
	// cleanup the all states
	while (!states.empty())
	{
		states.back()->Cleanup();

		delete states.back();
		states.pop_back();
	}

	std::cout << "AppEngine cleaned up." << std::endl;
}

void AppEngine::ChangeState(AppState* state)
{
	if (!states.empty()) 
	{
		states.back()->Cleanup();

		delete states.back();
		states.pop_back();
	}

	std::cout << "changing state" << std::endl;

	states.push_back(state);
	states.back()->Init(this);
}

void AppEngine::PushState(AppState* state)
{
	// pause current state
	if (!states.empty())
		states.back()->Pause();

	std::cout << "pushing state" << std::endl;

	// store and init the new state
	states.push_back(state);
	states.back()->Init(this);
}

void AppEngine::PopState()
{
	// cleanup the current state
	if (!states.empty())
	{
		states.back()->Cleanup();

		delete states.back();
		states.pop_back();
	}

	// resume previous state
	if (!states.empty())
		states.back()->Resume();
}

void AppEngine::PopState(int amount)
{
	for (size_t i = 0; i < amount; i++)
	{
		// cleanup the current state
		if (!states.empty())
		{
			states.back()->Cleanup();

			delete states.back();
			states.pop_back();
		}

		// resume previous state
		if (!states.empty())
			states.back()->Resume();
	}
}

void AppEngine::HandleEvents()
{
	if (running)
		states.back()->HandleEvents();
}

void AppEngine::Update()
{
	// let the state update the game
	if (running)
		states.back()->Update();
}

void AppEngine::Draw()
{
	// let the state draw the screen
	if (running)
		states.back()->Draw();
}

void AppEngine::Quit()
{
	std::cout << "AppEngine shutdown initiated." << std::endl;

	for (size_t i = 0; i < states.size(); i++)
	{
		states.back()->Cleanup();
		delete states.back();
		states.pop_back();
	}

	states.clear();

	running = false;
}
