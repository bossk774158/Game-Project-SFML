#pragma once
#include "Entity.h"
#include "EnemySpawner.h"

class Entity;
class EnemySpawner;

class Enemy :
    public Entity
{
private:
    //Variables
    EnemySpawner& enemySpawner;

    //Initializer functions
    void initVariables();
    void initAnimation();

public:
    Enemy(EnemySpawner& enemy_spawner, float x, float y, sf::Texture& texture_sheet);
    virtual ~Enemy();

    void updateAnimation(const float& dt);

    void update(const float& dt);
    void render(sf::RenderTarget& target);
};

