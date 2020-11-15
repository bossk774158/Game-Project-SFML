#pragma once
#include "Item.h"
class MeleeWeapon :
    public Item
{
public:
    MeleeWeapon(unsigned value);
    virtual ~MeleeWeapon();
};

