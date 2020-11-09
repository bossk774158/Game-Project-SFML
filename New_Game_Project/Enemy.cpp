#include "Enemy.h"

void Enemy::initVariables()
{

}

void Enemy::initAnimation()
{

	this->animationComponent->addAnimation("IDLE", 1.5f, 0, 0, 3, 0, 60, 36);
	this->animationComponent->addAnimation("WALK", 1.1f, 0, 1, 5, 1, 40, 36);
	this->animationComponent->addAnimation("ATTACK", 1.f, 0, 2, 6, 2, 34, 36);
}


//Constructors /Destructors 
Enemy::Enemy(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 55.f, 70.f);
	this->createMovementComponent(200.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);

	this->setPosition(x, y);
	this->initAnimation();
}

Enemy::~Enemy()
{

}

void Enemy::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(2.f, 2.f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(23.f, 0.f);
		this->sprite.setScale(-2.f, 2.f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}



void Enemy::update(const float& dt)
{
	this->movementComponent->update(dt);

	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	this->hitboxComponent->render(target);
}

