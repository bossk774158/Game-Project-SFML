#pragma once
#include "Entity.h"
#include "Items.h"


class Player :
    public Entity
{
private:
    //Varaibles
    sf::RectangleShape sword_shape;

    bool attacking;
    bool shoot;
    bool attacking_combo1;
    bool attacking_combo2;


    unsigned damageMin;
    unsigned damageMax;

    bool face;
    float shootCooldown;
    float shootCooldownMax;

    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;

    sf::Clock shootTimer;

    sf::Clock damageTimer;
    sf::Int32 damageTimerMax;

    //Initializer functions
    void initVariables();
    void initComponents();
    void initAnimation();


public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Accessors
    AttributeComponent* getAttributeComponent();
    const HitboxComponent* gethitbox() const;
    const unsigned& getDamageMin() const;
    const unsigned& getDamageMax() const;
    const unsigned getDamage() const;
    //const bool getAttackTimer() const;
    const bool getDamageTimer();

    //Functions
    void loseHP(const int hp);
    void gainHP(const int hp);
    void loseEXP(const int exp);
    void gainEXP(const int exp);

    const sf::Vector2f& getPos() const;
    const bool canShoot();
    

    void updateShoot(const float& dt);
    void update(const float& dt, const sf::View& view);
    void render(sf::RenderTarget& target);

};

