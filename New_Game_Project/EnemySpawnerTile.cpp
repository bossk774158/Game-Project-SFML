#include "EnemySpawnerTile.h"

EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF, const sf::Texture& texture, const sf::IntRect& texture_rect,
	int enemy_type, int enemy_amount, sf::Int32 enemy_time_to_spawn, float enemy_max_distance)
	:Tile(TileType::ENEMYSPAWNER, grid_x, grid_y,gridSizeF,texture,texture_rect, false)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->spawned = false;
}

EnemySpawnerTile::~EnemySpawnerTile()
{

}

const std::string EnemySpawnerTile::getAsSting() const
{
	std::stringstream ss;

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
		<< this->enemyType<< " " << this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemyMaxDistance;

	std::cout << ss.str() << "\n";

	return ss.str();
}

const bool& EnemySpawnerTile::getSpawned() const
{
	return this->spawned;
}

//Functions

void EnemySpawnerTile::setSpawned(const bool spawned)
{
	this->spawned = spawned;
}

const bool EnemySpawnerTile::canSpawn() const
{
	if (this->enemySpawnTimer.getElapsedTime().asMilliseconds() >= this->enemyTimeToSpawn)
	{
		return true;
	}
	return false;
}

void EnemySpawnerTile::update()
{
	if (this->canSpawn())
		this->spawned = false;
	this->enemySpawnTimer.restart();
}

void EnemySpawnerTile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
