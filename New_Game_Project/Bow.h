#pragma once
#include "RangedWeapon.h"
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

class RengedWeapon;

class Bow :
    public RangedWeapon
{
public:
    Bow(unsigned value);
    virtual ~Bow();

    virtual Bow* clone();

    virtual void update();
    virtual void render(sf::RenderTarget& target);
};

