#pragma once
#include "Enemy.h"
class Mummy :
    public Enemy
{
private:
    virtual void initVariables();
    virtual void initAnimation();
public:
    Mummy(float x, float y, sf::Texture& texture_sheet);
    virtual ~Mummy();

    virtual void updateAnimation(const float& dt);

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget& target);
};

