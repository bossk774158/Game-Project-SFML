#pragma once

#include "Item.h"

class Inventory
{
private:
	Item** itemArray;
	unsigned nrOfItem;
	unsigned capacity;

	void initialize();
	void nullify(const unsigned from = 0);
	void freeMemory();
public:
	Inventory(unsigned capacity);
	virtual ~Inventory();

	//accessors
	const unsigned& size() const;
	const unsigned& maxSize() const;

	//modifier

	//functions
	void clear();
	const bool empty() const;

	const bool add(Item* item);
	const bool remove(const unsigned index);

	const bool saveToFile(const std::string filename);
	const bool loadFromFile(const std::string filename);
};

