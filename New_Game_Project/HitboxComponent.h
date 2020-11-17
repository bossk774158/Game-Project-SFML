#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape* sword;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;
	float range;

public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();

	//Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);
	const unsigned& getRange() const;

	//Modifier
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	//Functions
	bool intersects(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};

