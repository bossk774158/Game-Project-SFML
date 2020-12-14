#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
class Arrow
{
private:
	sf::Sprite shape;
	sf::Texture* bullet_arrow;

	sf::Vector2f direction;
	float movementSpeed;

	bool flip;

public:
	Arrow();
	Arrow(sf::Texture* bullet_arrow,float pos_x, float pos_y, float dir_shoot_x, float dir_shoot_y, float movement_speed);
	~Arrow();

	//accessors
	sf::FloatRect getbounds() const;
	
	void flipArrow();
	const bool getFlipArrow();
	bool isIntersects(sf::FloatRect other);

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

