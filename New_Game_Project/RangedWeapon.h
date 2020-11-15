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

#include"Weapon.h"

class RangedWeapon :
	public Weapon
{
private:


protected:
	

public:
	RangedWeapon(unsigned level, unsigned value);
	virtual ~RangedWeapon();

	virtual RangedWeapon* clone() = 0;
	void generate(const unsigned levelMin, const unsigned levelMax);

	virtual void update() = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

