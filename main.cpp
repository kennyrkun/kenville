#include "AppEngine.hpp"
#include "MainMenuState.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
	std::cout << "starting" << std::endl;

	AppSettings settings = { "alpha", "kenville", { argc, argv } };

	AppEngine app;
	app.Init(settings);

	app.PushState(new MainMenuState);

	while (app.isRunning())
	{
		app.HandleEvents();
		app.Update();
		app.Draw();
	}

	return EXIT_SUCCESS;
}
