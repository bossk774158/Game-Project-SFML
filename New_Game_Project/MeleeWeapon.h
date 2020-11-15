#pragma once
#include "Weapon.h"
class MeleeWeapon :
    public Weapon
{
private:

protected:


public:
    MeleeWeapon(unsigned level, unsigned value);
    virtual ~MeleeWeapon();

    virtual MeleeWeapon* clone() = 0;
    virtual void generate(const unsigned levelMin, const unsigned levelMax);
};

