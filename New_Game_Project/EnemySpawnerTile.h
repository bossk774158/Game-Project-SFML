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

class EnemySpawnerTile
	:public Tile
{
private:
	int enemyType;
	int enemyAmount;
	int enemyCounter;
	sf::Clock enemySpawnTimer;
	sf::Int32 enemyTimeToSpawn;
	float enemyMaxDistance;
	bool firstSpawn;

	//Spawn Timer

public:
	EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
		int enemy_type, int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawnerTile();

	//Accessors
	virtual const std::string getAsSting() const;
	const int& getEnemyAmount()const;
	const int& getEnemyCounter() const;
	const bool getSpawnTimer();
	const int& getEnemyType() const;
	const float& getEnemyMaxDistance() const;
	//Modifiers

	//functions
	void increaseEnemyCounter();
	void decreaseEnemyCounter();

	void update();
	void render(sf::RenderTarget& target);
};

