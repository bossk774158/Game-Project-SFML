#include "Player.h"
//Initializer functions
void Player::initVariables()
{
	this->sprite.setScale(10.f,10.f);
	
}

void Player::initComponents()
{
	this->createMovementComponent(400.f,15.f,5.f);
}


//Constructors /Destructors 
Player::Player(float x,float y,sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 280.f, 315.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 1.5f, 0, 0, 3, 0, 60, 36);
	this->animationComponent->addAnimation("WALK", 1.1f, 0, 1, 5, 1, 40, 36);
	this->animationComponent->addAnimation("ATTACK", 1.5f, 0, 2, 6, 2, 34, 36);
}

Player::~Player()
{

}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(10.f, 10.f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x,this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(23.f, 0.f);
		this->sprite.setScale(-10.f, 10.f);
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
		

	this->hitboxComponent->update();
}
