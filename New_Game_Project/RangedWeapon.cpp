#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(unsigned level, unsigned value)
	:Weapon(level, value)
{
	this->type = ItemTypes::IT_RANGEDWEAPON;
}

RangedWeapon::~RangedWeapon()
{

}

void RangedWeapon::generate(const unsigned levelMin, const unsigned levelMax)
{

}
