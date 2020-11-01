#pragma once
#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
class Tile
{

private:


protected:
	sf::RectangleShape shape;

public:
	Tile();
	Tile(float x, float y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect);
	virtual ~Tile();

	//Functions
	void update();
	void render(sf::RenderTarget& target);

};

