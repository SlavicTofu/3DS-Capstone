#include "essential.hpp"
#include "actor.hpp"

#pragma once

#define TEXTURE_INDEX_FOR_LASER 2

class Laser : public Actor
{
public:
    Laser(float inX, float inY, float inRotation)
    {
        x = inX;
        y = inY;
        rotation = inRotation;
        setupSprite(&this->spr, TEXTURE_INDEX_FOR_LASER);
        hitbox = Rectangle(x, y, spr.image.subtex->height, spr.image.subtex->height);
        
        velocityVec = Vector2D(0,0);
        accelerationVec = Vector2D(0,0);
        acceleration = 1000;
        maxSpeed = 500;
        deceleration = 0;

        C2D_SpriteSetCenter(&this->spr, 0.5, 0.5);
        scaleHitbox(0.5);
    }

    void act(float dt) override
    {
        alignHitbox();
        accelerateForward();
        applyPhysics(dt);
    }
};