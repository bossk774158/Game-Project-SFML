#pragma once
#include "Entity.h"
#include "EnemySpawnerTile.h"

class Entity;
class EnemySpawnerTile;

class Enemy :
    public Entity
{
private:
    //Variables
    //EnemySpawnerTile& enemySpawner;
    unsigned gainExp;

    //Initializer functions
    virtual void initVariables() = 0;
    virtual void initAnimation() = 0;

public:
    Enemy();
    virtual ~Enemy();

    const unsigned& getGainExp() const;

    virtual void loseHP(const int hp);
    virtual const bool isDead() const;

    virtual const AttributeComponent* getAttributeComp() const;

    virtual void updateAnimation(const float& dt) = 0;

    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};

