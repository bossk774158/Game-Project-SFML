#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(unsigned level, unsigned value)
	:Weapon(level,value)
{
	this->type = ItemTypes::IT_MELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon()
{

}

void MeleeWeapon::generate(const unsigned levelMin, const unsigned levelMax)
{
	this->level = rand() % (levelMax - levelMin + 1) + levelMin;

	this->damageMin = this->level * (rand() % 2 + 1);
	this->damageMax = this->level * (rand() % 3 + 1) + this->damageMin;

	this->range = this->level + rand() % 10 + 50;

	this->value = this->level + this->damageMin + this->damageMax + this->range + (rand() & level * 10);
}
