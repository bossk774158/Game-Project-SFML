#include "Item.h"

void Item::initVarialbles()
{

}

Item::Item(unsigned value)
{
	this->initVarialbles();

	this->value = value;
	this->type = ItemTypes::IT_DEFAULT;
}

Item::~Item()
{
}
