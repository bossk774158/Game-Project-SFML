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
	moveVec.x = self.getPosition().x - entity.getPosition().x;
	moveVec.y = self.getPosition().x - entity.getPosition().y;
	float vecLenght = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));
	moveVec /= vecLenght;

	if (self.getPosition().x != entity.getPosition().x)
		self.move(moveVec.x, moveVec.y,dt);
}
