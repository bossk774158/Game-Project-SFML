#pragma once

#include "Entity.h"
#include "EnemySpawnerTile.h"
#include "RegularTile.h"

class Tile;
class Entity;
class EnemySpawnerTile;

class TileMap
{
private:
	void clear();

	float gridSizeF;
	int gridSizeI;
	sf::Vector2i maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	int layers;
	std::vector< std::vector< std::vector < std::vector<Tile*> > > > map;
	std::stack <Tile*> deferredRenderStack;
	std::string textureFile;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;



public:
	TileMap(float gridSizeF, int width, int height, std::string texture_file);
	virtual ~TileMap();

	//Accessors
	const bool tileEmpty(const int x, const int y, const int z) const;
	const sf::Texture* getTileSheet() const;
	const int getLayerSize(const int x, const int y, const int layer) const;


	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

	//Function
	void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type);
	void addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect,
		const int enemy_type, const int enemy_am, const int enemy_tts, const int enemy_md);
	void removeTile(const int x, const int y, const int z, const int type = -1);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);
	const bool checkType(const int x, const int y, const int z, const int type) const;

	void updateWorldBoundCollision(Entity* entity, const float& dt);
	void updateTilecollision(Entity* entity, const float& dt);
	void updateTiles(Entity* entity, const float& dt);
	void update(Entity* entity, const float& dt);

	void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition);
	void renderDeffered(sf::RenderTarget& target);

	
};


