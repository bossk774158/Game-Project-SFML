#pragma once
#include "Entity.h"
class Enemy :
    public Entity
{
private:
    //Variables


    //Initializer functions
    void initVariables();
    void initAnimation();

public:
    Enemy(float x, float y, sf::Texture& texture_sheet);
    virtual ~Enemy();

    void updateAnimation(const float& dt);

    void update(const float& dt);
    void render(sf::RenderTarget& target);
};

