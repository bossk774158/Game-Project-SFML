#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    //Varaibles
    bool attacking;

    //Initializer functions
    void initVariables();
    void initComponents();
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Functions
    void update(const float& dt);

    void render(sf::RenderTarget& target);

};

