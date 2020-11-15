#pragma once
#include "Enemy.h"
#include "AIFollow.h"
class Mummy :
    public Enemy
{
private:
    virtual void initVariables();
    virtual void initAnimation();
    void initAI();

    AIFollow* follow;

public:
    Mummy(float x, float y, sf::Texture& texture_sheet, Entity& player);
    virtual ~Mummy();

    virtual void updateAnimation(const float& dt);

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget& target);
};

