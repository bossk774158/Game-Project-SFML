#pragma once
#include "MeleeWeapon.h"
class Sword :
    public MeleeWeapon
{
private:
    Sword* sword;
public:
    Sword(unsigned value);
    virtual ~Sword();
};

