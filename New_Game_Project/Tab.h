#pragma once

#include"Player.h"
#include "GUI.h"

class Tab
{
protected:
	Player& player;
	sf::Font font;
	
	bool hidden;

public:
	Tab(sf::Font& font, Player& player, bool hidden);
	virtual ~Tab();

	//Accessors
	const bool& getHidden() const;
	const bool& getOpen() const;

	//Function
	void hide();
	void show();


	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

