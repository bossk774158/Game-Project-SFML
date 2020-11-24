#pragma once
#include "Entity.h"
#include "EnemySpawnerTile.h"

class Enemy :
    public Entity
{
private:
    bool isDrop;
    bool isDeath;

protected:
    //Variables
    EnemySpawnerTile& enemySpawnerTile;
    
    unsigned gainExp;
    sf::Clock damageTimer;
    sf::Int32 damageTimerMax;
    sf::Clock despawnTimer;
    sf::Int32 despawnTimerMax;

    //Initializer functions
    virtual void initVariables() = 0;
    virtual void initAnimation() = 0;

public:
    Enemy(EnemySpawnerTile& enemy_spawner_tile);
    virtual ~Enemy();

    //Accessors
    const unsigned& getGainExp() const;
    EnemySpawnerTile& getEnemySpawnerTile();
    const bool getDamageTimerDone() const;
    const bool getDespawnTimerDone() const;
    const bool enemyGetType() const;
    bool getIsDrop();
    bool getIsDeath();

    //Modifier
    void resetDamageTimer();

    virtual void generateAttributes(const unsigned level);

    virtual void loseHP_mummy(const int hp_mummy);
    virtual const bool mummyIsDead() const;

    virtual void loseHP_bird(const int hp_bird);
    virtual const bool birdIsDead() const;

    virtual void loseHP_boss(const int hp_boss);
    virtual const bool bossIsDead() const;

    virtual const AttributeComponent* getAttributeComp() const;

    virtual void updateAnimation(const float& dt) = 0;

    virtual void update(const float& dt, const sf::View& view) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
};

