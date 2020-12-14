#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
#include<math.h>

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>

#include "CharacterTab.h"


class PlayerGUITabs
{
private:

	CharacterTab characterTab;

	Player& player;
	sf::Font& font;
	sf::Clock keyTimer;
	float keyTimeMax;

	//Tab

	//Character Tab

	void initFont();
	void initKeyTime();

public:
	PlayerGUITabs(sf::Font& font, Player& player);
	virtual ~PlayerGUITabs();

	const bool getKeyTime();
	const bool tabsOpen();

	void update();
	void render(sf::RenderTarget& target);


};

