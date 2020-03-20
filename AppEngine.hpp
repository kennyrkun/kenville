#ifndef APP_ENGINE_HPP
#define APP_ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <string>

class AppState;

struct AppSettings
{
	std::string version = "1-20w07a";
	std::string title = "kenville " + version;

	struct CommandLineArguments
	{
		int argc;
		char** argv;
	} launchOptions;

	bool debug = true;

	struct Graphics
	{
		sf::VideoMode dimensions = { 1080, 720};
		bool vsync = true;
		bool console = false;
		bool useAnimations = true;
		float animationScale = 1;
		size_t maxfps = 60;

		size_t width = 1080;
		size_t height = 720;
	} graphics;

	struct Locale
	{
		int timezoneOffset = -6;
		bool fullTimeFormat = false;
	} locale;

	struct Server
	{
		sf::IpAddress serverIpAddress = sf::IpAddress::LocalHost;
		unsigned short serverPort = 12345;

		bool connected = false;
	} server;

	std::string workDir = "./kenvillee/";
};

struct Keybindings
{
	sf::Keyboard::Key movePlayerUp = sf::Keyboard::Key::W;
	sf::Keyboard::Key movePlayerLeft = sf::Keyboard::Key::A;
	sf::Keyboard::Key movePlayerDown = sf::Keyboard::Key::S;
	sf::Keyboard::Key movePlayerRight = sf::Keyboard::Key::D;
	sf::Keyboard::Key entityInteract = sf::Keyboard::Key::E;
};

class AppEngine
{
public:
	AppEngine();

	void Init(AppSettings settings_);
	void Cleanup();

	// Note: code after these functions is still executed.
	void ChangeState(AppState* state);
	void PushState(AppState* state);
	void PopState();
	// amount: the amount of states to pop starting from the back
	void PopState(int amount);

	void HandleEvents();
	void Update();
	void Draw();

	bool isRunning() { return running; }
	void Quit();

	AppSettings settings;

	sf::RenderWindow window;

	std::vector<AppState*> states;

	Keybindings keys;

private:
	bool running;
};

#endif // !APP_ENGINE_HPP
