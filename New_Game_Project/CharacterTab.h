#pragma once

#include "Tab.h"

class CharacterTab : public Tab
{
private:
	sf::RectangleShape back;
	sf::Text infoText;
	sf::Text topic;

	void initText();

public:
	CharacterTab(sf::Font& font, Player& player);
	~CharacterTab();

	void update();
	void render(sf::RenderTarget& target);
};

