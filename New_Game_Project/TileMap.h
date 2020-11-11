#pragma once
#include"Tile.h"
#include "Entity.h"

class Tile;
class Entity;

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
	void removeTile(const int x, const int y, const int z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void update(Entity* entity, const float& dt);

	void render(sf::RenderTarget& target, const sf::Vector2i& gridPosition);
	void renderDeffered(sf::RenderTarget& target);

	
};


