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
    Bow* bow;
    Sword* sword;

    bool face;

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

    //Functions
    void loseHP(const int hp);
    void gainHP(const int hp);
    void loseEXP(const int exp);
    void gainEXP(const int exp);

    const sf::Vector2f& getPos() const;


    void update(const float& dt);
    void render(sf::RenderTarget& target);

};

