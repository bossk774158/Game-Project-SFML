#pragma once
#include "MeleeWeapon.h"
class Sword :
    public MeleeWeapon
{
private:
    

public:
    Sword(unsigned level, unsigned value);
    virtual ~Sword();

    virtual Sword* clone();

    virtual void update();
    virtual void render(sf::RenderTarget& target);
};

