#pragma once
#include "Enemy.h"
#include "AIFollow.h"
class Bird :
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
    Bird(float x, float y, sf::Texture& texture_sheet, EnemySpawnerTile& enemy_spawner_tile, Entity& player);
    virtual ~Bird();

    virtual void updateAnimation(const float& dt);

    virtual void update(const float& dt, const sf::View& view);
    virtual void render(sf::RenderTarget& target);
};

