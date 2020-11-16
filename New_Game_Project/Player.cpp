#include "Player.h"
//Initializer functions
void Player::initVariables()
{
	this->sprite.setScale(2.f,2.f);
	this->attacking = false;
	this->shoot = false;
	this->bow = new Bow(1, 20);
	this->face = false;
	//this->sword->generate(1, 3);
	this->shootCooldownMax = 100.f;
	this->shootCooldown = this->shootCooldownMax;
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

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 55.f, 50.f);
	this->createMovementComponent(200.f, 1500.f, 500.f);
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


	//Sword //delete later
	this->sword_shape.setSize(sf::Vector2f(40.f, 10.f));
	this->sword_shape.setFillColor(sf::Color::Red);
	this->sword_shape.setOutlineColor(sf::Color::Green);
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
	//this->bow->update();
}

void Player::render(sf::RenderTarget& target)
{
	//target.draw(this->sword_shape);
	target.draw(this->sprite);
	
	//this->bow->render(target);
	

	this->hitboxComponent->render(target);
}
