#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	: sprite(sprite), offsetX(offset_x), offsetY(offset_y)
{
	this->sprite = sprite;
	this->offsetX = offset_x;
	this->offsetY = offset_y;
	this->hitbox.setPosition(sprite.getPosition().x + offset_x, sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
	this->hitbox.setOrigin(14.f, 16.f);
}

HitboxComponent::~HitboxComponent()
{
}

bool HitboxComponent::checkIntersect(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
