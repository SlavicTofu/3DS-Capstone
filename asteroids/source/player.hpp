#include "essential.hpp"
#include "spriteHandler.hpp"
#include "actor.hpp"

#pragma once

class Player : public Actor
{
public:
    Player(float inX, float inY, float index, std::vector<Actor*>& inActorList) : Actor(inActorList)
    {
        x = inX;
        y = inY;
        rotation = 0;
        rotationOffset = 90;

        velocityVec = Vector2D(0,0);
        accelerationVec = Vector2D(0,0);
        acceleration = 40;
        maxSpeed = 300;
        deceleration = 20;

        spr = initSprite(index);
        C2D_SpriteSetCenter(&spr->spr, 0.5, 0.7);
        hitbox = Rectangle(x, y, spr->spr.image.subtex->width, spr->spr.image.subtex->height);
        scaleHitbox(0.7);

        // add self to actor array

        actorList.push_back(this);
    }

    void act(float dt) override
    {
        alignHitbox();
        applyPhysics(dt);
        wrapAroundWorld();
    }
};