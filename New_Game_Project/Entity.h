#pragma once

#include"HitboxComponent.h"
#include"MovementComponent.h"
#include"AnimationComponent.h"
class Entity
{
private:
	void initVariables();
protected:

	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;

public:
	Entity();
	virtual ~Entity();

	//Component Funtions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);

	//Functions
	virtual void move(const float dir_x, const float dir_y, const float& dt);

	//Modifier
	virtual void setPosition(const float x, const float y);

	//Accessors
	virtual const sf::Vector2f& getPosition() const;
	
	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
};

