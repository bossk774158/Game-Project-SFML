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

	//enemy
	this->vitality_enemy = 3;
	this->strength_enemy = 3;
	this->dexterity_enemy = 1;
	this->agility_enemy = 1;
	this->intelligence_enemy = 1;

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

void AttributeComponent::enemyLoseHP(const int hp_enemy)
{
	this->hp_enemy -= hp_enemy;

	if (this->hp_enemy < 0)
		this->hp_enemy = 0;
}

const bool AttributeComponent::playerIsDead() const
{
	return this->hp_player == 0;
}

const bool AttributeComponent::enemyIsDead() const
{
	return this->hp_enemy == 0;
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

	this->hpMax_enemy = this->vitality_enemy * 5 + this->vitality_enemy + this->strength_enemy / 2 + this->intelligence_enemy / 5;
	this->damageMin_enemy = this->strength_enemy * 2 + this->strength_enemy / 4 + this->intelligence_enemy / 5;
	this->damageMax_enemy = this->strength_enemy * 2 + this->strength_enemy / 2 + this->intelligence_enemy / 5;

	if (reset)
	{
		this->hp_player = this->hpMax_player;
	}

	if (reset)
	{
		this->hp_enemy = this->hpMax_enemy;
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
		++this->strength;
		++this->vitality;
		++this->strength;
		++this->intelligence;
		this->hpMax_player += static_cast<int>((this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5) / 3);
		this->hp_player += 10;
	}
}

void AttributeComponent::update()
{
	this->updateLevel();
}
