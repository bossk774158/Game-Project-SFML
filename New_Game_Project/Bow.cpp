#include "Bow.h"

Bow::Bow(unsigned value)
	:RangedWeapon(value)
{
	
}

Bow::~Bow()
{

}

Bow* Bow::clone()
{
	return new Bow(*this);
}

void Bow::update()
{

}

void Bow::render(sf::RenderTarget& target)
{

}
