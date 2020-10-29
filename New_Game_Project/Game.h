#pragma once
#include"MainMenuState.h"
class Game
{
private:
	//Variable
	sf::RenderWindow* window;
	sf::Event sfEvent;


	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initializetion
	void initWindow();
	void initKeys();
	void initStates();

public:
	//Constructors/Destructors
	Game();
	virtual ~Game();



	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

