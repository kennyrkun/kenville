#include "GamePlayState.hpp"

#include <iostream>

// TODO: what the fuck is this
sf::CircleShape test;

void GamePlayState::Init(AppEngine* app_)
{
	app = app_;

	std::cout << "Initialising GamePlayState" << std::endl;

	// TODO: actually "create" the gameworld in GameCreationState, or maybe GameWorldLoadState

	std::cout << "Loading world texture..." << std::endl;

	worldTexture = new sf::Texture; // fix not running in debug

	if (!worldTexture->loadFromFile(app->settings.workDir + "resources/textures/world.jpeg"))
		std::cerr << "Failed to load world textures!" << std::endl;

	//TODO: make camera align with world center on game start
	world.setSize(sf::Vector2f(800, 600));
	world.setOrigin(sf::Vector2f(world.getSize().x / 2, world.getSize().y / 2));
	world.setPosition(sf::Vector2f(0, 0));
	world.setTexture(*&worldTexture);

	std::cout << "Preparing user interface elements..." << std::endl;

	test.setRadius(8);
	test.setOrigin(test.getLocalBounds().width / 2, test.getLocalBounds().height / 2);

	sf::Vector2f screendimensions;
	screendimensions.x = app->window.getSize().x / 2;
	screendimensions.y = app->window.getSize().y / 2;

	mainView2 = new sf::View(screendimensions, screendimensions);

	// TODO: clean up old viewanchor stuff
	viewAnchor = new sf::View(screendimensions, sf::Vector2f(app->window.getSize().x, app->window.getSize().y));

	mainView2->setCenter(sf::Vector2f(0, 0));

	std::cout << "GamePlayState ready!" << std::endl;
}

void GamePlayState::Cleanup()
{
	std::cout << "Cleaning up GamePlayState." << std::endl;

	app->window.setView(app->window.getDefaultView());

	delete mainView2;
	delete worldTexture;

	std::cout << "Cleaned up GamePlayState." << std::endl;
}

void GamePlayState::Pause()
{
	app->window.setView(app->window.getDefaultView());

	std::cout << "GamePlayState paused." << std::endl;
}

void GamePlayState::Resume()
{
	std::cout << "GamePlayState resumed." << std::endl;
}

void GamePlayState::HandleEvents()
{
	timePerFrame = sf::seconds(1.0f / 60.0f); // 60 frames per second
	timeSinceLastUpdate = sf::Time::Zero;

	sf::Time deltaTime = deltaClock.restart();  // get elapsed time and reset clock
	timeSinceLastUpdate += deltaTime;

//	if (timeSinceLastUpdate >= timePerFrame)
	{
		timeSinceLastUpdate -= timePerFrame;

		sf::Event event;
		while (app->window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed)
			{
				app->Quit();
				return;		
			}
			else if (event.type == sf::Event::EventType::KeyPressed)
			{
				/*
				if (event.key.code == sf::Keyboard::Key::Escape)
				{
					app->PushState(new GamePauseState);
					return;
				}
				else if (event.key.code == sf::Keyboard::Key::Space)
				{
					if (!entMan->selectedEnts.empty())
					{
						std::cout << "centering mainview on selected entity");

						mainView2->setCenter(entMan->selectedEnts[0]->sprite.getPosition());

						// TODO: do we want to do this?
						mainView2->view.setRotation(0);
					}
				}
				*/
			 	if (event.key.code == sf::Keyboard::Key::LShift)
				{
					baseViewSpeed = 250;
				}
				/*
				else if (event.key.code == sf::Keyboard::Key::F12)
				{
					util::screenshot(*app->window);

					app->window.clear(sf::Color::White);
					app->window.display();
				}
				*/
				else if (event.key.code == sf::Keyboard::Key::Tilde)
				{
					app->settings.debug = !app->settings.debug;

					std::cout << "cl_debug set to " + std::to_string(app->settings.debug) << std::endl;
				}
			}
			else if (event.type == sf::Event::EventType::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Key::LShift)
				{
					baseViewSpeed = 500;
				}
			}
			else if (event.type == sf::Event::EventType::MouseWheelMoved)
			{
				// TODO: make this a variable of the Camera class
				static float zoomlevel = 2.0f;

				if (event.mouseWheel.delta < 0) // up (in)
				{
					if (zoomlevel <= 4)
					{
						mainView2->zoom(2.0f);
						zoomlevel *= 2.0f;
					}
				}
				else if (event.mouseWheel.delta > 0) // down (out)
				{
					if (zoomlevel > 0.5f)
					{
						mainView2->zoom(0.5f);
						zoomlevel *= 0.5f;
					}
				}
			}
		} // pollevent

		if (app->window.hasFocus())
		{
			updateGameCamera();

			// todo: clamp the mouse and keep it in the window

			//float frames_per_second = framesClock.restart().asSeconds();
			//debugFrameCounter.setString("FPS: " + std::to_string(static_cast<int>(1.0f / frames_per_second)));
		} // app->window.hasFocus()

		sf::Time deltaTime = deltaClock.restart();  // get elapsed time and reset clock
		timeSinceLastUpdate += deltaTime;
	}
}

void GamePlayState::Update()
{
}

void GamePlayState::Draw()
{
	app->window.clear();
	
	// ------------ MAIN VIEW
	app->window.setView(*mainView2);

	app->window.draw(world);

	// ------------- ANCHOR
	app->window.setView(*viewAnchor);

	// Draw the UI here

	app->window.display();
}

// Private

void GamePlayState::updateGameCamera()
{
	int moveX = 0, moveY = 0;
	int moveAmount = baseViewSpeed * timePerFrame.asSeconds();

	// keyboard based camera movement
	if (sf::Keyboard::isKeyPressed(app->keys.moveCameraUp))
		moveY -= moveAmount;
	if (sf::Keyboard::isKeyPressed(app->keys.moveCameraDown))
		moveY += moveAmount;
	if (sf::Keyboard::isKeyPressed(app->keys.moveCameraLeft))
		moveX -= moveAmount;
	if (sf::Keyboard::isKeyPressed(app->keys.moveCameraRight))
		moveX += moveAmount;

	/*
	if (app->settings.mouseMoveEnabled)
	{
		// mouse based camera movement
		float width = app->settings.mouseMoveBorderWidth;
		sf::FloatRect left(0, 0, width, app->window.getSize().y);
		sf::FloatRect right(app->window.getSize().x - width, 0, width, app->window.getSize().y);
		sf::FloatRect up(0, 0, app->window.getSize().x, width);
		sf::FloatRect down(0, app->window.getSize().y - width, app->window.getSize().x, width);

		sf::Vector2f mousePos = app->window.mapPixelToCoords(sf::Mouse::getPosition(app->window), *viewAnchor);

		if (up.contains(mousePos))
			moveY -= moveAmount;
		if (down.contains(mousePos))
			moveY += moveAmount;
		if (left.contains(mousePos))
			moveX -= moveAmount;
		if (right.contains(mousePos))
			moveX += moveAmount;
	}
	*/

	sf::Vector2f newPosition = mainView2->getCenter() + sf::Vector2f(moveX, moveY);

	newPosition.x = std::clamp(newPosition.x, -400.f, 400.f);
	newPosition.y = std::clamp(newPosition.y, -300.f, 300.f);

	mainView2->setCenter(newPosition);
}

