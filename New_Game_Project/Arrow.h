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

public:
	Arrow();
	Arrow(sf::Texture* bullet_arrow,float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed);
	~Arrow();

	//accessors
	sf::FloatRect getbounds() const;

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

