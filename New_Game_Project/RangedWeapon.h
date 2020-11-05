#pragma once

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>

#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>

#include"Item.h"

class Item;

class RangedWeapon :
	public Item
{
private:

protected:
	sf::Texture spriteRengedWeapon;
	sf::Sprite rengedweapon_sprite;

	int damageMin;
	int damageMax;

public:
	RangedWeapon();
	virtual ~RangedWeapon();

	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

