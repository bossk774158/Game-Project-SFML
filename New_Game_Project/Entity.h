#pragma once

#include"HitboxComponent.h"
#include"MovementComponent.h"
#include"AnimationComponent.h"
#include "AttributeComponent.h"
#include"SkillComponent.h"

class HitboxComponent;
class MovementComponent;
class AnimationComponent;
class AttributeComponent;
class SkillComponent;

class Entity
{
private:
	void initVariables();
protected:

	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;
	SkillComponent* skillcomponent;

public:
	Entity();
	virtual ~Entity();

	//Component Funtions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent(const unsigned level);
	void createSkillComponent();
	void createAIComponent();

	//Functions
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	//Modifier
	virtual void setPosition(const float x, const float y);

	//Accessors
	virtual MovementComponent* getMovementcomponent();
	virtual AnimationComponent* getAnimationComponent();
	virtual AttributeComponent* getAttributeComponent();
	virtual SkillComponent* getSkillComponent();

	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2f& getSpritePosition() const;
	virtual const sf::Vector2f getCenter() const;
	virtual const sf::Vector2f getSpriteCenter() const;
	virtual const sf::Vector2i getGridPosition(const int gridSizeI) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;

	//Calculations
	virtual const float getDistance(const Entity& entity) const;
	
	virtual void update(const float& dt, const sf::View& view) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

