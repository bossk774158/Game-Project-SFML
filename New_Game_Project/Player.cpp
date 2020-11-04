#include "Player.h"
//Initializer functions
void Player::initVariables()
{
	this->sprite.setScale(3.f,3.f);
	this->attacking = false;
	
}

void Player::initComponents()
{

}


//Constructors /Destructors 
Player::Player(float x,float y,sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 95.f, 115.f);
	this->createMovementComponent(400.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(0);

	this->animationComponent->addAnimation("IDLE", 1.5f, 0, 0, 3, 0, 60, 36);
	this->animationComponent->addAnimation("WALK", 1.1f, 0, 1, 5, 1, 40, 36);
	this->animationComponent->addAnimation("ATTACK", 1.f, 0, 2, 6, 2, 34, 36);
}

Player::~Player()
{

}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}

	if (this->attacking)
	{
		if(this->animationComponent->play("ATTACK", dt, true))
			this->attacking = false;
	}

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(3.f, 3.f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x,this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(23.f, 0.f);
		this->sprite.setScale(-3.f, 3.f);
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

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
