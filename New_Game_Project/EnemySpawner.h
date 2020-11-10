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

class EnemySpawner
{
private:
	sf::RectangleShape shape;

	sf::Vector2i gridPosition;
	int type;
	int amount;
	int timeToSpawn;
	float maxDistance;

public:
	EnemySpawner(sf::Vector2i grid_position, float gird_size, int type, int amount, int time_to_spawn, float max_distance);
	virtual ~EnemySpawner();

	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

