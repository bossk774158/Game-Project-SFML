#pragma once
#include "State.h"
#include "GUI.h"
#include "MainMenuState.h"

class VictoryState :
    public State
{
private:
	//Resources
	sf::Font font;
	sf::Text menuText;

	sf::Music vic_music;

	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Texture backgroundTexture;

	std::map<std::string, gui::Button*> buttons;

	sf::Music bg_music;


	//Functions
	void initVariables();
	void initMusic();
	void initBackground();
	void initFonts();
	void initButtons();
	void initKeybinds();

public:
	VictoryState(StateData* state_data);
	virtual ~VictoryState();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void endState();
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);

	//Accessors
	std::map<std::string, gui::Button*>& getButtons();

	//Render
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target);

};

