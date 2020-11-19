#include "EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
	int enemy_type, int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance)
	:Tile(TileType::ENEMYSPAWNER, grid_x, grid_y,gridSizeF,texture,texture_rect, false)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyCounter = 0;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->firstSpawn = true;
}

EnemySpawnerTile::~EnemySpawnerTile()
{

}

const std::string EnemySpawnerTile::getAsSting() const
{
	std::stringstream ss;

	ss << this->type << " " 
		<< this->shape.getTextureRect().left << " " 
		<< this->shape.getTextureRect().top << " "
		<< this->enemyType<< " " 
		<< this->enemyAmount << " " 
		<< this->enemyTimeToSpawn << " " 
		<< this->enemyMaxDistance;

	//std::cout << ss.str() << "\n";

	return ss.str();
}

const int& EnemySpawnerTile::getEnemyAmount() const
{
	return this->enemyAmount;
}

const int& EnemySpawnerTile::getEnemyCounter() const
{
	return this->enemyCounter;
}

const bool EnemySpawnerTile::getSpawnTimer()
{
	if (this->enemySpawnTimer.getElapsedTime().asSeconds() >= this->enemyTimeToSpawn || this->firstSpawn)
	{
		this->enemySpawnTimer.restart();
		this->firstSpawn = false;
		return true;
	}
	return false;
}

//Functions

void EnemySpawnerTile::increaseEnemyCounter()
{
	if (this->enemyCounter < this->enemyAmount)
		++this->enemyCounter;
}

void EnemySpawnerTile::decreaseEnemyCounter()
{
	if (this->enemyCounter > 0)
		--this->enemyCounter;
}

void EnemySpawnerTile::update()
{

}

void EnemySpawnerTile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
