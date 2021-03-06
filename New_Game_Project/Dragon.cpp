#include "Dragon.h"

void Dragon::initVariables()
{
	this->sprite.setScale(1.5f, 1.5f);
}

void Dragon::initAnimation()
{
	this->animationComponent->addAnimation("ATTACK", 1.f, 0, 0, 4, 0, 180, 130);
	this->animationComponent->addAnimation("WALK", 1.f, 0, 1, 4, 1, 120, 130);
	this->animationComponent->addAnimation("IDLE", 1.5f, 0, 2, 2, 2, 240, 130);
	this->animationComponent->addAnimation("DEATH", 1.f, 0, 3, 4, 3, 120, 130);
}

void Dragon::initGui()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(55.f, 7.f));
	this->hpBar.setPosition(this->sprite.getPosition());
}

void Dragon::initAI()
{

}

Dragon::Dragon(float x, float y, sf::Texture& texture_sheet, Entity& player)
	:Enemy(enemySpawnerTile)
{
	this->initVariables();
	this->initGui();

	this->createHitboxComponent(this->sprite, 0.f, 30.f, 100.f, 120.f);
	this->createMovementComponent(200.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->generateAttributes(this->attributeComponent->level);

	this->setPosition(x, y);
	this->initAnimation();

	this->follow = new AIFollow(*this, player);
}

Dragon::~Dragon()
{
	delete this->follow;
}

void Dragon::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(1.5f, 1.5f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(60.f, 0.f);
		this->sprite.setScale(-1.5f, 1.5f);
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

	if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax)
	{
		this->sprite.setColor(sf::Color::Red);
	}
	else
		this->sprite.setColor(sf::Color::White);
}

void Dragon::update(const float& dt, const sf::View& view)
{
	Enemy::update(dt, view);

	this->movementComponent->update(dt);

	this->hpBar.setSize(sf::Vector2f(145.f * (static_cast<float>(this->attributeComponent->hp_boss) / this->attributeComponent->hpMax_boss), 15.f));
	this->hpBar.setPosition(this->sprite.getPosition().x-20, this->sprite.getPosition().y+ 30.f);

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	

	this->follow->update(dt);
}

void Dragon::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	target.draw(this->hpBar);

	this->hitboxComponent->render(target);
}
