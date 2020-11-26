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
private:
	std::map<std::string, sf::SoundBuffer*> soundEffects;

	sf::Sound levelUp;

	void initSound();
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

	//All about mummy
	int hp_mummy;
	int hpMax_mummy;
	int damageMin_mummy;
	int damageMax_mummy;
	int vitality_mummy;
	int strength_mummy;
	int dexterity_mummy;
	int agility_mummy;
	int intelligence_mummy;
	int accuracy_mummy;
	int defence_mummy;
	int luck_mummy;

	//All about bird
	int hp_bird;
	int hpMax_bird;
	int damageMin_bird;
	int damageMax_bird;
	int vitality_bird;
	int strength_bird;
	int dexterity_bird;
	int agility_bird;
	int intelligence_bird;
	int accuracy_bird;
	int defence_bird;
	int luck_bird;

	//All about boss
	int hp_boss;
	int hpMax_boss;
	int damageMin_boss;
	int damageMax_boss;
	int vitality_boss;
	int strength_boss;
	int dexterity_boss;
	int agility_boss;
	int intelligence_boss;
	int accuracy_boss;
	int defence_boss;
	int luck_boss;

	//Player Stats
	int hp_player;
	int hpMax_player;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;

	sf::Clock stats;

	//Con /De
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	//Functions
	std::string debugPrint() const;

	void loseExp(const int exp);
	void gainExp(const int exp);
	void loseHP(const int hp);
	void gainHP(const int hp);
	void getStrength(const int str);

	void mummyLoseHP(const int hp_enemy_mummy);
	void birdLoseHP(const int hp_enemy_bird);
	void bossLoseHP(const int hp_boss);

	const bool playerIsDead() const;
	const bool mummyIsDead() const;
	const bool birdIsDead() const;
	const bool bossIsDead() const;
	

	void updateState(const bool reset);
	void updateLevel();

	void update();
};

