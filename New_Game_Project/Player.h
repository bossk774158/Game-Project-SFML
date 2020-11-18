#pragma once
#include "Entity.h"
#include "Items.h"
#include "Inventory.h"

class Player :
    public Entity
{
private:
    //Varaibles
    Inventory* inventory;
    sf::RectangleShape sword_shape;

    bool attacking;
    bool shoot;
    Bow* bow;

    unsigned damageMin;
    unsigned damageMax;

    bool face;
    float shootCooldown;
    float shootCooldownMax;

    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;

    //Initializer functions
    void initVariables();
    void initComponents();
    void initAnimation();
    void initInventory();

public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Accessors
    AttributeComponent* getAttributeComponent();
    const Weapon* getWeapon() const;
    const HitboxComponent* gethitbox() const;
    const unsigned& getDamageMin() const;
    const unsigned& getDamageMax() const;
    const unsigned getDamage() const;
    //const bool getAttackTimer() const;

    //Functions
    void loseHP(const int hp);
    void gainHP(const int hp);
    void loseEXP(const int exp);
    void gainEXP(const int exp);

    const sf::Vector2f& getPos() const;
    const bool canShoot();
    

    void updateShoot(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget& target);

};

