#include "essential.hpp"
#include "spriteHandler.hpp"
#include "actor.hpp"

#pragma once

class Asteroid : public Actor
{
public:

    int stage;

    Asteroid(float inX, float inY, int inStage, int inRotation)
    {
        x = inX;
        y = inY;

        rotation = inRotation;

        acceleration = 100;
        maxSpeed = 1 * 0.1 * stage;

        int sprIndex = 0;

        stage = inStage;

        switch(stage)
        {
            case 1: sprIndex = (rand() % 4) + 5; break;
            case 2: sprIndex = (rand() % 2) + 9; break;
            case 3: sprIndex = (rand() % 2) + 11; break;
            case 4: sprIndex = (rand() % 2) + 13; break;
            default: sprIndex = (rand() % 4) + 5; break;
        }
        setupSprite(&this->spr, sprIndex);
        C2D_SpriteSetCenter(&this->spr, 0.5, 0.5);
        hitbox = Rectangle(x, y, spr.image.subtex->width, spr.image.subtex->height);
        scaleHitbox(0.7f);

        accelerateForward();
    }

    void act(float dt) override
    {
        if(rotationOffset >= 360) rotationOffset = 0;
        rotationOffset += 100 * dt;
        moveBy(accelerationVec.x * dt, accelerationVec.y * dt);
        wrapAroundWorld();
        alignHitbox();
    }
};