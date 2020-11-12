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

enum TileType {DEFAULT = 0, DAMAGING, TOPTILE, ENEMYSPAWNER};

class Tile
{

private:


protected:
	sf::RectangleShape shape;
	bool collision;
	short type;

public:
	Tile();
	Tile(short type ,int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect, const bool collision);
	virtual ~Tile();

	//Accessors
	const short& getType() const;

	//Functions
	virtual const bool& getCollision() const;
	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const bool intersects(const sf::FloatRect bounds) const;
	virtual const std::string getAsSting() const = 0;

	void setBound(bool bounded);
	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target) = 0;

};

