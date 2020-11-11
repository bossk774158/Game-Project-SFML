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

#include "Tile.h"

class Tile;

class EnemySpawner
	:public Tile
{
private:
	int enemyType;
	int enemyAmount;
	int enemyTimeToSpawn;
	float enemyMaxDistance;

public:
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		float gird_size, int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawner();

	void update();
	void render(sf::RenderTarget& target);
};

