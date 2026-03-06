#include "essential.hpp"
#include "spriteHandler.hpp"
#include "actor.hpp"

#pragma once

class Asteroid : public Actor
{
public:
    Asteroid(float inX, float inY, float index)
    {
        x = inX;
        y = inY;
        spr = initSprite(index);
        hitbox = Rectangle(x, y, spr->spr.image.subtex->width, spr->spr.image.subtex->height);
    }

    void act(float dt) override
    {
        y++;
        x++;
        wrapAroundWorld();
    }
};