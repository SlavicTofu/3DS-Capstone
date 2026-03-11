#include "essential.hpp"
#include "spriteHandler.hpp"
#include "actor.hpp"

#pragma once

class Laser : public Actor
{
private:
    float lifeTime = 5;
public:
    Laser(float inX, float inY, float index, std::vector<Actor*>& inActorList) : Actor(inActorList)
    {
        x = inX;
        y = inY;
        spr = initSprite(index);
        hitbox = Rectangle(x, y, spr->spr.image.subtex->width, spr->spr.image.subtex->height);
        
        velocityVec = Vector2D(0,0);
        accelerationVec = Vector2D(0,0);
        acceleration = 0;
        maxSpeed = 100;
        deceleration = 0;
        
        // add self to actor array

        actorList.push_back(this);
    }

    void act(float dt) override
    {
        accelerateForward();
        wrapAroundWorld();

        if(lifeTime < 0)
        {
            dispose();
        }
        else
        {
            lifeTime -= dt;
        }
    }
};