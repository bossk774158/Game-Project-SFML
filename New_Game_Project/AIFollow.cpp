#include "AIFollow.h"

AIFollow::AIFollow(Entity& self, Entity& entity)
	:AIOption(self,entity)
{

}

AIFollow::~AIFollow()
{

}

void AIFollow::update(const float& dt)
{
	sf::Vector2f moveVec;
	moveVec.x = entity.getPosition().x - self.getPosition().x;
	moveVec.y = entity.getPosition().y - self.getPosition().x;

	float vecLenght = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLenght;

	if (self.getPosition().x != entity.getPosition().x && std::abs(vecLenght) < 400.f)
		self.move(moveVec.x, moveVec.y,dt);
}
