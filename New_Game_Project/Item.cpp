#include "Item.h"

void Item::initVarialbles()
{

}

Item::Item(unsigned level, unsigned value)
{
	this->initVarialbles();

	this->level = level;
	this->value = value;
	this->type = ItemTypes::IT_DEFAULT;
}

Item::~Item()
{

}
