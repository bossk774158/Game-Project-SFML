#pragma once
#include "Entity.h"
class Player :
    public Entity
{
private:
    //Varaibles

    //Initializer functions
    void initVariables();
    void initComponents();
public:
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();

    //Functions

};

