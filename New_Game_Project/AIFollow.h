#pragma once
#include "AIOption.h"

class AIFollow :
    public AIOption
{
protected:
    

public:
    AIFollow(Entity& self, Entity& entity);
    ~AIFollow();

    void update(const float& dt);
};

