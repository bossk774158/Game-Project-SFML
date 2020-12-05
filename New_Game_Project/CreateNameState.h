#pragma once
#include "State.h"
#include "GameState.h"
class CreateNameState :
    public State
{
private:
	sf::Event nameEvent;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::RectangleShape textHolder;

	sf::Font font;
	sf::String input;
	std::string nameString;
	sf::Text text;

	Player* player;

	std::map<std::string, gui::Button*> buttons;

	sf::Music bg_music;

	//Initializer
	void initVariables();
	void initMusic();
	void initFont();
	void initText();
	void initKeybinds();
	void initButtons();

public:
	CreateNameState(StateData* state_data);
	virtual ~CreateNameState();

	//Functions
	void endState();
	void updateButtons();
	void updateInput(const float& dt);
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

