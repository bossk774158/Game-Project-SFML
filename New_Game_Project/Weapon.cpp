#include "Weapon.h"

void Weapon::initVariables()
{
	this->range = 35;
}

Weapon::Weapon(unsigned level, unsigned value)
	:Item(level,value)
{
	this->initVariables();
}

Weapon::~Weapon()
{

}

const unsigned& Weapon::getRange() const
{
	return this->range;
}
