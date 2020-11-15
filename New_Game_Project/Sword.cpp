#include "Sword.h"

Sword::Sword(unsigned level, unsigned value)
	:MeleeWeapon(level,value)
{

}
Sword::~Sword()
{

}

Sword* Sword::clone()
{
	return new Sword(*this);
}

void Sword::update()
{
	
}

void Sword::render(sf::RenderTarget& target)
{
	
}
