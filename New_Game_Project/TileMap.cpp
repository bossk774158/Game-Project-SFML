#include "TileMap.h"

void TileMap::clear()
{
	if (!this->map.empty())
	{
		for (int x = 0; x < this->map.size(); x++)
		{
			for (int y = 0; y < this->map[x].size(); y++)
			{
				for (int z = 0; z < this->map[x][y].size(); z++)
				{
					for (size_t k = 0; k < this->map[x][y][z].size(); k++)
					{
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = NULL;
					}
					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}
		this->map.clear();
	}
	//std::cout << this->map.size() << "\n";
}

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<unsigned>(this->gridSizeF);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->toX = maxSizeWorldGrid.x;
	this->fromY = 0;
	this->toY = maxSizeWorldGrid.y;
	this->layer = 0;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector < std::vector< std::vector<Tile*> > >());
	for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (int y = 0; y < maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector < std::vector<Tile*>>());

			for (int z = 0; z < layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector <Tile*>());
			}
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))
	{
		std::cout << "EROOR::TILEMAP::FAILED TO LOAD TEXTURESHEET::FILENAME" << texture_file << "\n";
	}

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(250, 0, 0, 50));
}

TileMap::~TileMap()
{
	this->clear();
}

const bool TileMap::tileEmpty(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maxSizeWorldGrid.x &&
		y >= 0 && y < this->maxSizeWorldGrid.y &&
		z >= 0 && z < this->layers)
	{
		return this->map[x][y][z].empty();
	}

	throw("ERROR::TILEMAP::TILEEMPTY::TRYING TO ACCESS OUT OF BOUNDS TILE");
}

//Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

const int TileMap::getLayerSize(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < static_cast<int>(this->map.size()))
	{
		if (y >= 0 && y < static_cast<int>(this->map[x].size()))
		{
			if (layer >= 0 && layer < static_cast<int>(this->map[x][y].size()))
			{
				return this->map[x][y][layer].size();
			}
		}
	}
	return -1;
}

void TileMap::addTile(const int x, const int y, const int z, const sf::IntRect& texture_rect, const bool& collision, const short& type)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z <= layers && z >= 0)
	{
			this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect,collision,type));
			std::cout << "DEBUG: ADD TILE" << "\n";
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z <= layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			delete this->map[x][y][z][this->map[x][y][z].size()-1];
			this->map[x][y][z].pop_back();
			std::cout << "DEBUG: REMOVED TILE" << "\n";
		}
	}
}

void TileMap::saveToFile(const std::string file_name)
{
	std::ofstream out_file;

	out_file.open(file_name);

	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< this->layers << "\n"
			<< this->textureFile << "\n";

		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < maxSizeWorldGrid.y; y++)
			{
				for (int z = 0; z < layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (size_t k = 0; k < this->map[x][y][z].size(); k++)
						{
							out_file << x << " " << y << " " << z << " " << this->map[x][y][z][k]->getAsSting() << " ";
						}
					}
				}
			}
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP:: COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
	}

	out_file.close();
}


void TileMap::loadFromFile(const std::string file_name)
{
	std::ifstream in_file;

	in_file.open(file_name);

	if (in_file.is_open())
	{
		sf::Vector2i size;
		int gridSize = 0;
		int layers = 0;
		std::string texture_file = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int trX = 0;
		int trY = 0;
		bool collision = false;
		short type = 0;

		//Basics
		in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

		//Tiles
		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSizeWorldGrid.x = size.x;
		this->maxSizeWorldGrid.y = size.y;
		this->layers = layers;
		this->textureFile = texture_file;

		this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector < std::vector<std::vector<Tile*> > >());
		for (int x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (int y = 0; y < maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<std::vector<Tile*>>());

				for (int z = 0; z < layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		if (!this->tileSheet.loadFromFile(texture_file))
		{
			std::cout << "EROOR::TILEMAP::FAILED TO LOAD TEXTURESHEET::FILENAME" << texture_file << "\n";
		}
		//Load all tiles
		while (in_file >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z].push_back(
				new Tile(
				x, y,
				this->gridSizeF,
				this->tileSheet,
				sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI),
				collision,
				type));
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP:: COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}

	in_file.close();
}

void TileMap::update(Entity* entity, const float& dt)
{
	//WORLD BOUNDS
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorldF.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorldF.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}


	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{
			for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
			{
				this->map[x][y][this->layer][k]->update();

				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = this->map[x][y][this->layer][k]->getGlobalBounds();
				sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

				if (this->map[x][y][this->layer][k]->getCollision() &&
					this->map[x][y][this->layer][k]->intersects(nextPositionBounds)
					)
				{
					//std::cout << playerBounds.left << " " << playerBounds.top << " " << wallBounds.left << " " << wallBounds.top << "\n";
					std::cout << "Collision\n";
					//Bottom collision
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						std::cout << "Bottom Collision\n";
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}

					//Top collision
					else if (playerBounds.top > wallBounds.top
						&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left
						)
					{
						std::cout << "Top Collision\n";
						entity->stopVelocityY();
						//entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
					}

					//Right collision
					else if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						std::cout << "Right Collision\n";
						entity->stopVelocityX();
						//entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}

					//Left collision
					else if (playerBounds.left > wallBounds.left
						&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top
						)
					{
						std::cout << "Left Collision\n";
						entity->stopVelocityX();
						//entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
					}
				}
			}
		}
	}
}

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPosition)
{

		for (int x = this->fromX; x < this->toX; x++)
		{
			for (int y = this->fromY; y < this->toY; y++)
			{
				for (size_t k = 0; k < this->map[x][y][this->layer].size(); k++)
				{
					if (this->map[x][y][this->layer][k]->getType() == TileType::TOPTILE)
					{
						this->deferredRenderStack.push(this->map[x][y][this->layer][k]);
					}
					else
					{
						this->map[x][y][this->layer][k]->render(target);
					}
					if (this->map[x][y][this->layer][k]) {
						if (this->map[x][y][this->layer][k]->getCollision())
						{
							this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
							target.draw(this->collisionBox);
						}
					}
				}
			}
		}
}

void TileMap::renderDeffered(sf::RenderTarget& target)
{
	while (this->deferredRenderStack.empty())
	{
		deferredRenderStack.top()->render(target);
		deferredRenderStack.pop();
	}
}


