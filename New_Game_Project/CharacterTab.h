#pragma once

#include "Tab.h"

class CharacterTab : public Tab
{
private:
	sf::RectangleShape back;
	sf::Text infoText;

public:
	CharacterTab(sf::Font& font, Player& player);
	~CharacterTab();

	void update();
	void render(sf::RenderTarget& target);
};

