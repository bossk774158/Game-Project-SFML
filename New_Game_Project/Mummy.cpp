#include "Mummy.h"

void Mummy::initVariables()
{
	this->sprite.setScale(1.5f, 1.5f);
}

void Mummy::initAnimation()
{
	this->animationComponent->addAnimation("IDLE", 1.5f, 0, 0, 3, 0, 60, 45);
	this->animationComponent->addAnimation("ATTACK_LEFT", 1.1f, 0, 1, 5, 1, 40, 45);
	this->animationComponent->addAnimation("WALK_LEFT", 1.f, 0, 2, 5, 2, 40, 45);
	this->animationComponent->addAnimation("WALK_RIGHT", 1.f, 0, 3, 5, 3, 40, 45);
	this->animationComponent->addAnimation("ATTACK_RIGHT", 1.1f, 0, 4, 5, 4, 40, 45);
}

void Mummy::initGui()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(55.f, 7.f));
	this->hpBar.setPosition(this->sprite.getPosition());
}

void Mummy::initAI()
{
	
}

Mummy::Mummy(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player)
	: Enemy(enemy_spawner_tile)
{
	this->initVariables();
	this->initGui();

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 45.f, 40.f);
	this->createMovementComponent(200.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->generateAttributes(this->attributeComponent->level);

	this->setPosition(x, y);
	this->initAnimation();

	this->follow = new AIFollow(*this, player);
}
	

Mummy::~Mummy()
{
	delete this->follow;
}

void Mummy::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(1.5f, 1.5f);
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(20.f, 0.f);
		this->sprite.setScale(-1.5f, 1.5f);
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}

	if (this->damageTimer.getElapsedTime().asMilliseconds() <= this->damageTimerMax)
	{
		this->sprite.setColor(sf::Color::Red);
	}
	else
		this->sprite.setColor(sf::Color::White);
}



void Mummy::update(const float& dt, const sf::View& view)
{
	Enemy::update(dt, view);

	this->movementComponent->update(dt);

	this->hpBar.setSize(sf::Vector2f(55.f * (static_cast<float>(this->attributeComponent->hp_mummy) / this->attributeComponent->hpMax_mummy), 7.f));
	this->hpBar.setPosition(this->sprite.getPosition());

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->follow->update(dt);
}

void Mummy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	target.draw(this->hpBar);

	this->hitboxComponent->render(target);
}
