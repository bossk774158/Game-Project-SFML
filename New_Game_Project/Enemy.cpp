#include "Enemy.h"
#include "VectorMath.h"

void Enemy::initVariables()
{
	this->gainExp = 15;
	this->damageTimerMax = 1000;
	this->despawnTimerMax = 1000;

	this->isDrop = true;
}

void Enemy::initAnimation()
{

}


//Constructors /Destructors 
Enemy::Enemy(EnemySpawnerTile& enemy_spawner_tile)
	:enemySpawnerTile(enemy_spawner_tile)
{
	this->initVariables();
	this->initAnimation();
}

Enemy::~Enemy()
{

}

const unsigned& Enemy::getGainExp() const
{
	return this->gainExp;
}

EnemySpawnerTile& Enemy::getEnemySpawnerTile()
{
	return this->enemySpawnerTile;
}

const bool Enemy::getDamageTimerDone() const
{
	return this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax;
}

const bool Enemy::getDespawnTimerDone() const
{
	return this->despawnTimer.getElapsedTime().asMilliseconds() >= this->despawnTimerMax;
}

const bool Enemy::enemyGetType() const
{
	return enemySpawnerTile.getEnemyType();
}

bool Enemy::getIsDrop()
{
	return this->isDrop;
}

bool Enemy::getIsDeath()
{
	return this->isDeath;
}

void Enemy::resetDamageTimer()
{
	this->damageTimer.restart();
}

void Enemy::generateAttributes(const unsigned level)
{
	this->gainExp = level * (rand() % 20 + 10);
}

void Enemy::loseHP_mummy(const int hp_mummy)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->mummyLoseHP(hp_mummy);
	}
}

const bool Enemy::mummyIsDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->mummyIsDead();
	}
	return false;
}

void Enemy::loseHP_bird(const int hp_bird)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->birdLoseHP(hp_bird);
	}
}

const bool Enemy::birdIsDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->birdIsDead();
	}
	return false;
}

void Enemy::loseHP_boss(const int hp_boss)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->birdLoseHP(hp_boss);
	}
}

const bool Enemy::bossIsDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->bossIsDead();
	}
	return false;
}

const AttributeComponent* Enemy::getAttributeComp() const
{
	if (this->attributeComponent)
		return this->attributeComponent;
	else
	{
		std::cout << "ERROR::ATTRIBUTECOMPONENT IS NOT INITIALIZE" << "\n";
		return nullptr;
	}
		
}

void Enemy::update(const float& dt, const sf::View& view)
{
	if (vectorDistance(this->getPosition(), view.getCenter()) < 550.f)
		this->despawnTimer.restart();
}
