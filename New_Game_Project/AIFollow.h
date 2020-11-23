#pragma once
#include "AIOption.h"

class AIFollow :
    public AIOption
{
protected:
    

public:
    AIFollow(Entity& self, Entity& entity);
    ~AIFollow();

    virtual void update(const float& dt);
};

