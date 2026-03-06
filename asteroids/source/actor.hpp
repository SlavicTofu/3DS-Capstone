#include "essential.hpp"
#include "spriteHandler.hpp"

#pragma once

class Actor
{
private:
    float vx, vy;
public:
    float x, y, direction;
    Sprite* spr;
    Rectangle hitbox;

    Actor()
    {
        x = 100;
        y = 100;
        spr = initSprite(0);
        hitbox = Rectangle(x, y, spr->spr.image.subtex->width, spr->spr.image.subtex->height);
    }
    Actor(float inX, float inY, float index)
    {
        x = inX;
        y = inY;
        spr = initSprite(index);
        hitbox = Rectangle(x, y, spr->spr.image.subtex->width, spr->spr.image.subtex->height);
    }

    virtual void act(float dt)
    {
        spr->x = x;
        spr->y = y;
    }

};