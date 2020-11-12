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

    //Initializer functions
    virtual void initVariables() = 0;
    virtual void initAnimation() = 0;

public:
    Enemy();
    virtual ~Enemy();

    virtual void updateAnimation(const float& dt) = 0;

    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};

