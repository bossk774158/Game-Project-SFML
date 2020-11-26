#include "Bird.h"
void Bird::initVariables()
{
	this->sprite.setScale(1.5f, 1.5f);
}

void Bird::initAnimation()
{

	this->animationComponent->addAnimation("IDLE", 1.5f, 0, 1, 3, 1, 37, 30);
	this->animationComponent->addAnimation("WALK_LEFT", 1.f, 0, 0, 3, 0, 37, 30);
	this->animationComponent->addAnimation("WALK_RIGHT", 1.f, 0, 2, 3, 2, 37, 30);
}

void Bird::initGui()
{
	this->hpBar.setFillColor(sf::Color::Red);
	this->hpBar.setSize(sf::Vector2f(55.f, 7.f));
	this->hpBar.setPosition(this->sprite.getPosition());
}

void Bird::initAI()
{

}

Bird::Bird(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player)
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


Bird::~Bird()
{
	delete this->follow;
}

void Bird::updateAnimation(const float& dt)
{
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
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



void Bird::update(const float& dt, const sf::View& view)
{
	Enemy::update(dt, view);

	this->movementComponent->update(dt);

	this->hpBar.setSize(sf::Vector2f(55.f * (static_cast<float>(this->attributeComponent->hp_bird) / this->attributeComponent->hpMax_bird), 7.f));
	this->hpBar.setPosition(this->sprite.getPosition());

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->follow->update(dt);
}

void Bird::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	target.draw(this->hpBar);

	this->hitboxComponent->render(target);
}
