#include "essential.hpp"
#include "spriteHandler.hpp"
#include "actor.hpp"

#pragma once

class Asteroid : public Actor
{
public:
    Asteroid(float inX, float inY, float index, std::vector<Actor*>& inActorList) : Actor(inActorList)
    {
        x = inX;
        y = inY;
        spr = initSprite(index);
        hitbox = Rectangle(x, y, spr->spr.image.subtex->width, spr->spr.image.subtex->height);
        
        // add self to actor array

        actorList.push_back(this);
    }

    void act(float dt) override
    {
        y++;
        x++;
        wrapAroundWorld();
    }
};