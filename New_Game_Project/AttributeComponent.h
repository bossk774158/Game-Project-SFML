#pragma once
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
#include<math.h>

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
class AttributeComponent
{
public:
	//Leveling
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoints;

	//Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

	//Con /De
	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();

	//Functions
	std::string debugPrint() const;

	void gainExp(const unsigned exp);

	void updateState(const bool reset);
	void updateLevel();

	void update();
};

