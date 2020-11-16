#include "Arrow.h"

Arrow::Arrow()
{
	
}

Arrow::Arrow(sf::Texture* bullet_arrow, float pos_x, float pos_y, float dir_x, float dir_y, float movement_speed)
{
	this->shape.setTexture(*bullet_arrow);

	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_x;
	this->direction.y = dir_y;
	this->movementSpeed = movement_speed;
}

Arrow::~Arrow()
{

}

sf::FloatRect Arrow::getbounds() const
{
	return this->shape.getGlobalBounds();
}

void Arrow::update(const float& dt)
{
	this->shape.move(this->movementSpeed * this->direction * dt);
}

void Arrow::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
