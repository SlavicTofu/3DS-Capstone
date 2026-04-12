#include "essential.hpp"
#include "spriteHandler.hpp"
#include "actor.hpp"

#pragma once

#define TEXTURE_INDEX_FOR_PLAYER 1

class Player : public Actor
{
private:
    Vector2D inputVec;
    float rotationSmoothness = 3;
    int health;
public:

    bool shooting = false;

    Player(float inX, float inY)
    {
        x = inX;
        y = inY;
        rotation = 0;
        rotationOffset = 90;

        inputVec = Vector2D(0,0);

        velocityVec = Vector2D(0,0);
        accelerationVec = Vector2D(0,0);
        acceleration = 60;
        maxSpeed = 300;
        deceleration = 5;

        health = 5;

        setupSprite(&this->spr, TEXTURE_INDEX_FOR_PLAYER);
        C2D_SpriteSetCenter(&this->spr, 0.5, 0.7);
        hitbox = Rectangle(x, y, spr.image.subtex->width, spr.image.subtex->height);
        scaleHitbox(0.7);
    }

    void act(float dt) override
    {
        alignHitbox();
        applyPhysics(dt);
        wrapAroundWorld();
    }

    void handleInput(float dt, u32 kDown, u32 kHeld, circlePosition pos)
    {
        // movement
        
        inputVec.set(pos.dx, -pos.dy); // Y is negative to account for Y positive going down

        float length = inputVec.len();

        if(length > 0)
        {
            float newRot = inputVec.toDegrees();
            float rotDistance = newRot - rotation;

            while (rotDistance < -180) rotDistance += 360;
            while (rotDistance > 180)  rotDistance -= 360;

            rotation = lerp(rotation, rotation + rotDistance, rotationSmoothness * dt);
        }
        if(length > 50) accelerateForward();

        // shooting

        if(kDown & KEY_A)
        {
            shooting = true;
        }
    }
};