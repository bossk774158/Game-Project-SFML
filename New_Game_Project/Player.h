#pragma once
#include "Entity.h"
#include "Bow.h"
class Player :
    public Entity
{
private:
    //Varaibles
    bool attacking;
    Bow bow;

    //Initializer functions
    void initVariables();
    void initComponents();
    void initAnimation();

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


    void update(const float& dt);
    void render(sf::RenderTarget& target);

};

