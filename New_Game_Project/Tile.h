#pragma once
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

enum TileType {DEFAULT = 0, DAMAGING};

class Tile
{

private:


protected:
	sf::RectangleShape shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		bool collision = false, short type = TileType::DEFAULT);
	virtual ~Tile();

	//Functions
	const bool& getCollision() const;
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const std::string getAsSting() const;

	void setBound(bool bounded);
	void update();
	void render(sf::RenderTarget& target);

};

