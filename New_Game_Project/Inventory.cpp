#include "Inventory.h"


void Inventory::initialize()
{
	this->nrOfItem = 0;
	this->itemArray = new Item*[this->capacity];

	this->nullify();
}

void Inventory::nullify(const unsigned from)
{
	for (size_t i = from; i < this->capacity; i++)
	{
		this->itemArray[i] = nullptr;
	}
}

void Inventory::freeMemory()
{
	for (size_t i = 0; i < this->nrOfItem; i++)
	{
		delete this->itemArray[i];
	}
	delete[] this->itemArray;
}

Inventory::Inventory(unsigned capacity)
{
	this->capacity = capacity;

	this->initialize();
}

Inventory::~Inventory()
{
	this->freeMemory();
}

const unsigned& Inventory::size() const
{
	return this->nrOfItem;
}

const unsigned& Inventory::maxSize() const 
{
	return this->capacity;
}

void Inventory::clear()
{
	for (size_t i = 0; i < this->nrOfItem; i++)
	{
		delete this->itemArray[i];
	}

	this->nrOfItem = 0;

	this->nullify();
}

const bool Inventory::empty() const
{
	return this->nrOfItem == 0;
}

const bool Inventory::add(Item* item)
{
	if (this->nrOfItem < this->capacity)
	{
		this->itemArray[this->nrOfItem++] = item->clone();

		return true;
	}

	return false;
}

const bool Inventory::remove(const unsigned index)
{
	if (this->nrOfItem > 0)
	{
		if (index < 0 || index >= this->capacity)
			return false;

		delete this->itemArray[index];
		this->itemArray[index] = nullptr;
		--this->nrOfItem;

		return true;
	}
	return false;
}

const bool Inventory::saveToFile(const std::string filename)
{
	return false;
}

const bool Inventory::loadFromFile(const std::string filename)
{
	return false;
}
