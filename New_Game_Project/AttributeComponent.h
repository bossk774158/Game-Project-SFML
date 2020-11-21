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
	int level;
	int exp;
	int expNext;
	int attributePoints;

	//Attributes
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;

	//All about enemies
	int hp_enemy;
	int hpMax_enemy;
	int damageMin_enemy;
	int damageMax_enemy;
	int vitality_enemy;
	int strength_enemy;
	int dexterity_enemy;
	int agility_enemy;
	int intelligence_enemy;
	int accuracy_enemy;
	int defence_enemy;
	int luck_enemy;


	//Stats
	int hp_player;
	int hpMax_player;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

	//Con /De
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	//Functions
	std::string debugPrint() const;

	void loseExp(const int exp);
	void gainExp(const int exp);
	void loseHP(const int hp);
	void gainHP(const int hp);

	void enemyLoseHP(const int hp_enemy);

	const bool playerIsDead() const;
	const bool enemyIsDead() const;
	

	void updateState(const bool reset);
	void updateLevel();

	void update();
};

