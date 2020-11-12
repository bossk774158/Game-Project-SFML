#pragma once
#include "Tile.h"

#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>

class RegularTile :
	public Tile
{
private:

protected:
	

public:
	RegularTile(short type, int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false);
	virtual ~RegularTile();

	//Functions
	virtual const std::string getAsSting() const;

	virtual void update();
	virtual void render(sf::RenderTarget& target);
};

