#pragma once

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>



enum ItemTypes {IT_DEFAULT = 0, IT_RANGEDWEAPON, IT_MELEEWEAPON};

class Item
{
private:
	void initVarialbles();
	
protected:
	//variables
	short unsigned type;
	unsigned level;
	unsigned value;

public:
	Item(unsigned level, unsigned value);
	virtual ~Item();

	//Accessors
	const short unsigned& getType() const { return this->type; };
	const unsigned& getLevel() const { return this->level; };
	const unsigned& getValue() const { return this->value; };

	//functions
	virtual Item* clone() = 0;
};

