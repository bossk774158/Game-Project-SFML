#pragma once
#include "Enemy.h"
#include "AIFollow.h"
class Dragon :
    public Enemy
{
private:
    virtual void initVariables();
    virtual void initAnimation();
    void initGui();
    void initAI();

    sf::RectangleShape hpBar;

    AIFollow* follow;

public:
    Dragon(float x, float y, sf::Texture& texture_sheet, Entity& player);
    virtual ~Dragon();

    virtual void updateAnimation(const float& dt);

    virtual void update(const float& dt, const sf::View& view);
    virtual void render(sf::RenderTarget& target);
};

