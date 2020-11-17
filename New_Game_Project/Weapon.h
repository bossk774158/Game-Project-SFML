 #pragma once

#include "Item.h"

class Weapon :
    public Item
{
private:
    void initVariables();

protected:
    sf::Texture spriteRengedWeapon;
    sf::Sprite rengedweapon_sprite;

    unsigned damageMin;
    unsigned damageMax;
    unsigned range;


public:
    Weapon(unsigned level, unsigned value);
    virtual ~Weapon();

    //accessors
    const unsigned& getDamageMin() const;
    const unsigned& getDamageMax() const;
    const unsigned& getRange() const;

    virtual Item* clone() = 0;
    virtual void generate(const unsigned levelMin, const unsigned levelMax) = 0;

    virtual void update() = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};

