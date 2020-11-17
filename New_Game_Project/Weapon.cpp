#include "Weapon.h"

void Weapon::initVariables()
{
	this->damageMin = 1;
	this->damageMax = 2;
}

Weapon::Weapon(unsigned level, unsigned value)
	:Item(level,value)
{
	this->initVariables();
}

Weapon::~Weapon()
{

}

const unsigned& Weapon::getDamageMin() const
{
	return this->damageMin;
}

const unsigned& Weapon::getDamageMax() const
{
	return this->damageMax;
}

const unsigned& Weapon::getRange() const
{
	return this->range;
}
