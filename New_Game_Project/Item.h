#pragma once

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>



enum ItemTypes {IT_DEFAULT = 0, IT_RANGEDWEAPON, IT_MELEEWEAPON};

class Item
{
private:
	sf::Texture texture;
	sf::RectangleShape shape;
	std::string type;

	void initVarialbles();
	

public:
	Item(sf::Texture* texture, std::string type, float x, float y);
	~Item();

	//Accessors
	sf::FloatRect getGlobalBounds();
	const std::string& getType() const;

	//Functions
	void update();

	//Render
	void render(sf::RenderTarget& target);
};

