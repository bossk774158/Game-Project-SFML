 #include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies,
	std::map<std::string, sf::Texture>& textures, Entity& player)
	: textures(textures), activeEnemies(activeEnemies), player(player)
{
	this->textures = textures;
	this->activeEnemies = activeEnemies;
}

EnemySystem::~EnemySystem()
{

}

void EnemySystem::createEnemy(const short type,const float xPos, const float yPos, EnemySpawnerTile& enemy_spawner_tile)
{
	//std::cout << "Create Enemy\n";
	switch (type)
	{
	case EnemyTypes::MUMMY:
		this->activeEnemies.push_back(new Mummy(xPos, yPos, this->textures["MUMMY_IDLE"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	case EnemyTypes::BIRD:
		this->activeEnemies.push_back(new Bird(xPos, yPos, this->textures["BIRD_IDLE"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;
	case EnemyTypes::DEMON:
		this->activeEnemies.push_back(new Dragon(xPos, yPos, this->textures["DRAGON_IDLE"], enemy_spawner_tile, this->player));
		enemy_spawner_tile.increaseEnemyCounter();
		break;

	default:
		std::cout << "ERROR::ENEMYSYSTEM::CREATENEMY::TYPE DOES NOT EXIST" << "\n";
		break;
	}
}

void EnemySystem::removeEnemy(const int index)
{
	this->activeEnemies[index]->getEnemySpawnerTile().decreaseEnemyCounter();
	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}

void EnemySystem::update(const float& dt)
{
	
}

void EnemySystem::render(sf::RenderTarget* target)
{

}
