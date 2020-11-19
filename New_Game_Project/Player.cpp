#include "Player.h"
//Initializer functions
void Player::initVariables()
{
	this->sprite.setScale(2.f,2.f);
	this->attacking = false;
	this->shoot = false;
	this->face = false;

	this->shootCooldownMax = 100.f;
	this->shootCooldown = this->shootCooldownMax;

	this->damageMin = 1;
	this->damageMax = 2;

	this->attackTimer.restart();
	this->attackTimerMax = 500;

	this->damageTimerMax = 500;

	this->bow = new Bow(1, 20);
}

void Player::initComponents()
{

}

void Player::initAnimation()
{

}

void Player::initInventory()
{
	this->inventory = new Inventory(100);
}

//Constructors /Destructors 
Player::Player(float x,float y,sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 55.f, 70.f);
	
	this->createMovementComponent(200.f, 1000.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();

	this->setPosition(x, y);
	this->initAnimation();

	this->initInventory();

	this->animationComponent->addAnimation("IDLE", 1.5f, 0, 0, 3, 0, 60, 36);
	this->animationComponent->addAnimation("WALK", 1.1f, 0, 1, 5, 1, 40, 36);
	this->animationComponent->addAnimation("ATTACK", 1.f, 0, 2, 6, 2, 34, 36);
	this->animationComponent->addAnimation("SHOOT", 1.f, 0, 3, 6, 3, 34, 36);
}

Player::~Player()
{
	delete this->inventory;
	delete this->bow;
}

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

const Weapon* Player::getWeapon() const
{
	return this->bow;
}

const HitboxComponent* Player::gethitbox() const
{
	return this->hitboxComponent;
}

const unsigned& Player::getDamageMin() const
{
	return this->damageMin;
}

const unsigned& Player::getDamageMax() const
{
	return this->damageMax;
}

const unsigned Player::getDamage() const
{
	return rand() % (
		(this->attributeComponent->damageMax + this->getDamageMax())
		- (this->attributeComponent->damageMin + this->getDamageMin()) + 1)
		+ (this->attributeComponent->damageMin + this->getDamageMin());
}

const bool Player::getDamageTimer()
{
	if (this->damageTimer.getElapsedTime().asMilliseconds() >= this->damageTimerMax)
	{
		this->damageTimer.restart();
		return true;
	}
	return false;
}

//const bool Player::getAttackTimer()
//{
//	std::cout << this->attackTimer.getElapsedTime().asMilliseconds() << "\n";
//	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
//	{
//		this->attackTimer.restart();
//		return true;
//	}
//	return false;
//}

void Player::loseHP(const int hp)
{
	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->exp -= exp;

	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainEXP(const int exp)
{
	this->attributeComponent->gainExp(exp);
}

const sf::Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}

const bool Player::canShoot()
{
	if (this->shootCooldown >= this->shootCooldownMax)
	{
		this->shootCooldown = 0.f;
		return true;
	}
	return false;
}

void Player::updateShoot(const float& dt)
{
	if (this->shootCooldown < this->shootCooldownMax)
		this->shootCooldown += 0.5f;
}

void Player::update(const float& dt)
{
	this->updateShoot(dt);
	this->movementComponent->update(dt);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}

	if (this->attacking)
	{
		if (this->animationComponent->play("ATTACK", dt, true))
			this->attacking = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		this->shoot = true;
	}
	if (this->shoot)
	{
		if (this->animationComponent->play("SHOOT", dt, true))
			this->shoot = false;
	}

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->face = false;
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(2.f, 2.f);
		this->sword_shape.setScale(1.f, 1.f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->face = true;
		this->sprite.setOrigin(23.f, 0.f);
		this->sprite.setScale(-2.f, 2.f);
		this->sword_shape.setScale(-1.f, 1.f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if(this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}

	this->hitboxComponent->update();
	this->sword_shape.setPosition(this->sprite.getPosition().x + 30.f, this->sprite.getPosition().y + 30.f);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	

	this->hitboxComponent->render(target);
}
