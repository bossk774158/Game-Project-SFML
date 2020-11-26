#include "Player.h"
//Initializer functions
void Player::initVariables()
{
	this->sprite.setScale(2.f,2.f);
	this->attacking = false;
	this->attacking_combo1 = false;
	this->shoot = false;
	this->face = false;

	this->shootCooldownMax = 100.f;
	this->shootCooldown = this->shootCooldownMax;

	this->damageMin = 1;
	this->damageMax = 2;

	this->attackTimer.restart();
	this->attackTimerMax = 500;

	this->damageTimerMax = 2000;

}

void Player::initComponents()
{

}

void Player::initAnimation()
{

}

//Constructors /Destructors 
Player::Player(float x,float y,sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, -7.f, 0.f, 50.f, 50.f);
	this->hitboxComponent->setPosition(this->getSpriteCenter());
	
	this->createMovementComponent(200.f, 1000.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();

	this->setPosition(x, y);
	this->initAnimation();

	this->animationComponent->addAnimation("IDLE", 1.5f, 0, 0, 3, 0, 60, 36);
	this->animationComponent->addAnimation("WALK", 1.1f, 0, 1, 5, 1, 40, 36);
	this->animationComponent->addAnimation("ATTACK", 0.7f, 0, 2, 6, 2, 34, 36);
	this->animationComponent->addAnimation("SHOOT", 0.5f, 0, 3, 6, 3, 34, 36);
	
}

Player::~Player()
{
	
}

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
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

const bool& Player::getIsFaceRight()
{
	return this->face;
}

const bool& Player::getIsShoot()
{
	return this->shoot;
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
	this->attributeComponent->hp_player -= hp;

	if (this->attributeComponent->hp_player < 0)
		this->attributeComponent->hp_player = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp_player += hp;

	if (this->attributeComponent->hp_player > this->attributeComponent->hpMax_player)
		this->attributeComponent->hp_player = this->attributeComponent->hpMax_player;
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

void Player::update(const float& dt, const sf::View& view)
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
	
	////Combo1
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	//{
	//	this->attacking_combo1 = true;
	//}

	//if (this->attacking_combo1)
	//{
	//	if (this->animationComponent->play("ATTACK_COMBO1", dt, true))
	//		this->attacking_combo1 = false;
	//}

	////Combo2
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	//{
	//	this->attacking_combo2 = true;
	//}

	//if (this->attacking_combo2)
	//{
	//	if (this->animationComponent->play("ATTACK_COMBO2", dt, true))
	//		this->attacking_combo2 = false;
	//}

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
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->face = true;
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

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
	

	this->hitboxComponent->render(target);
}
