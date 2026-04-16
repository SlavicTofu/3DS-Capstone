#include "essential.hpp"
#include "actor.hpp"

#pragma once

#define TEXTURE_INDEX_FOR_LASER 2
#define LASER_DURATION 1

class Laser : public Actor
{
public:
    float lifeTime;

    Laser(float inX, float inY, float inRotation)
    {
        x = inX;
        y = inY;
        rotation = inRotation;
        setupSprite(&this->spr, TEXTURE_INDEX_FOR_LASER);
        hitbox = Rectangle(x, y, spr.image.subtex->height, spr.image.subtex->height);
        
        type = LASER;

        velocityVec = Vector2D(0,0);
        accelerationVec = Vector2D(0,0);
        acceleration = 1000;
        maxSpeed = 500;
        deceleration = 0;

        lifeTime = LASER_DURATION;

        C2D_SpriteSetCenter(&this->spr, 0.5f, 0.5f);
        scaleHitbox(0.5);
    }

    void act(float dt) override
    {
        lifeTime -= dt;

        alignHitbox();
        accelerateForward();
        applyPhysics(dt);
        wrapAroundWorld();
    }

    void draw() override
    {
        C2D_SpriteSetPos(&this->spr, x, y);
        C2D_SpriteSetRotationDegrees(&this->spr, rotation + rotationOffset);
        C2D_SpriteSetScale(&this->spr, 1.2*(lifeTime/LASER_DURATION), 1.2*(lifeTime/LASER_DURATION));
        C2D_DrawSprite(&this->spr);
    }
};