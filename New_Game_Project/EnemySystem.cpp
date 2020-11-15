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

void EnemySystem::createEnemy(const short type,const float xPos, const float yPos)
{
	switch (type)
	{
	case EnemyTypes::MUMMY:
		this->activeEnemies.push_back(new Mummy(xPos, yPos, this->textures["MUMMY_IDLE"], this->player));
		break;
	default:
		std::cout << "ERROR::ENEMYSYSTEM::CREATENEMY::TYPE DOES NOT EXIST" << "\n";
		break;
	}
}

void EnemySystem::update(const float& dt)
{
	
}

void EnemySystem::render(sf::RenderTarget* target)
{

}
