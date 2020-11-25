#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = (50 * pow(this->level, 3) - 150 * pow(this->level, 2) + (UINT64)400 * this->level) / 3;
	this->attributePoints = 2;

	//player
	this->vitality = 10;
	this->strength = 5;
	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;

	//mummy
	this->vitality_mummy = 3;
	this->strength_mummy = 3;
	this->dexterity_mummy = 1;
	this->agility_mummy = 1;
	this->intelligence_mummy = 1;

	//bird
	this->vitality_bird = 10;
	this->strength_bird = 6;
	this->dexterity_bird = 3;
	this->agility_bird = 3;
	this->intelligence_bird = 3;

	//boss
	this->vitality_boss = 50;
	this->strength_boss = 30;
	this->dexterity_boss = 20;
	this->agility_boss = 20;
	this->intelligence_boss = 20;

	this->updateLevel();
	this->updateState(true);
}

AttributeComponent::~AttributeComponent()
{
	
}

std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss <<  "Level" << this->level << "\n"
		<< "Exp" << this->exp <<"\n"
		<< "Exp next: " << this->expNext <<"\n"
		<< "Attp:" << this->attributePoints << "\n";
	return ss.str();
}

void AttributeComponent::loseExp(const int exp)
{
	this->exp -= exp;

	if (this->exp < 0)
		this->exp = 0;
}

void AttributeComponent::gainExp(const int exp)
{
	this->exp += exp;

	this->updateLevel();
}

void AttributeComponent::loseHP(const int hp)
{
	this->hp_player -= hp;

	if (this->hp_player < 0)
		this->hp_player = 0;
}

void AttributeComponent::gainHP(const int hp)
{
	this->hp_player += hp;

	if (this->hp_player > this->hpMax_player)
		this->hp_player = this->hpMax_player;
}

void AttributeComponent::getStrength(const int str)
{
	this->strength += str;
	std::cout << "Got stronger!" << "\n";

	updateState(true);

	
	std::cout << this->strength << "\n";
}

void AttributeComponent::mummyLoseHP(const int hp_enemy_mummy)
{
	this->hp_mummy -= hp_enemy_mummy;

	if (this->hp_mummy < 0)
		this->hp_mummy = 0;
}

void AttributeComponent::birdLoseHP(const int hp_enemy_bird)
{
	this->hp_bird -= hp_enemy_bird;

	if (this->hp_bird < 0)
		this->hp_bird = 0;
}

void AttributeComponent::bossLoseHP(const int hp_boss)
{
	this->hp_boss -= hp_boss;

	if (this->hp_boss < 0)
		this->hp_boss = 0;
}

const bool AttributeComponent::playerIsDead() const
{
	return this->hp_player == 0;
}

const bool AttributeComponent::mummyIsDead() const
{
	return this->hp_mummy == 0;
}

const bool AttributeComponent::birdIsDead() const
{
	return this->hp_bird == 0;
}

const bool AttributeComponent::bossIsDead() const
{
	return this->hp_boss == 0;
}

//Functions
void AttributeComponent::updateState(const bool reset)
{
	this->hpMax_player	= this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5;
	this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->accuracy  = this->dexterity * 5 + this->dexterity / 2 + this->intelligence / 5;
	this->defence   = this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck		= this->intelligence * 2 + this->intelligence / 5;

	this->hpMax_mummy = this->vitality_mummy * 5 + this->vitality_mummy + this->strength_mummy / 2 + this->intelligence_mummy / 5;
	this->damageMin_mummy = this->strength_mummy * 2 + this->strength_mummy / 4 + this->intelligence_mummy / 5;
	this->damageMax_mummy = this->strength_mummy * 2 + this->strength_mummy / 2 + this->intelligence_mummy / 5;

	this->hpMax_bird = this->vitality_bird * 5 + this->vitality_bird + this->strength_bird / 2 + this->intelligence_bird / 5;
	this->damageMin_bird = this->strength_bird * 2 + this->strength_bird / 4 + this->intelligence_bird / 5;
	this->damageMax_bird = this->strength_bird * 2 + this->strength_bird / 2 + this->intelligence_bird / 5;

	this->hpMax_boss = this->vitality_boss * 5 + this->vitality_boss + this->strength_boss / 2 + this->intelligence_boss / 5;
	this->damageMin_boss = this->strength_boss * 2 + this->strength_boss / 4 + this->intelligence_boss / 5;
	this->damageMax_boss = this->strength_boss * 2 + this->strength_boss / 2 + this->intelligence_boss / 5;

	if (reset)
	{
		this->hp_player = this->hpMax_player;
	}

	if (reset)
	{
		this->hp_mummy = this->hpMax_mummy;
	}

	if (reset)
	{
		this->hp_bird = this->hpMax_bird;
	}

	if (reset)
	{
		this->hp_boss = this->hpMax_boss;
	}
}

void AttributeComponent::updateLevel()
{
	while (this->exp >= this->expNext)
	{
		++this->level;
		this->exp -= this->expNext;
		this->expNext = (50 * pow(this->level, 3) - 150 * pow(this->level, 2) + (UINT64)400 * this->level) / 3;
		++this->attributePoints;
		this->strength += 2;
		this->vitality += 2;
		this->strength += 2;
		this->intelligence += 2;
		this->hpMax_player += static_cast<int>((this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5) / 3);
		this->hp_player = this->hpMax_player;
	}
}

void AttributeComponent::update()
{
	this->updateLevel();
}
