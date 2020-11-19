#include "Enemy.h"
#include "VectorMath.h"

void Enemy::initVariables()
{
	this->gainExp = 15;
	this->damageTimerMax = 1000;
	this->despawnTimerMax = 1000;
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

void Enemy::resetDamageTimer()
{
	this->damageTimer.restart();
}

void Enemy::generateAttributes(const unsigned level)
{
	this->gainExp = level * (rand() % 20 + 10);
}

void Enemy::loseHP(const int hp)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(hp);
	}
}

const bool Enemy::isDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();
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
	if (vectorDistance(this->getPosition(), view.getCenter()) < 700.f)
		this->despawnTimer.restart();
}
