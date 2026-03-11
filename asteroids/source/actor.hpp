#include "essential.hpp"
#include "spriteHandler.hpp"
#include <algorithm>

#pragma once

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 400

class Actor
{
protected:
    std::vector<Actor*>& actorList;
public:
    float x, y, rotation, rotationOffset, acceleration, maxSpeed, deceleration;
    Vector2D velocityVec, accelerationVec;
    Sprite* spr;
    Rectangle hitbox;

    Actor(std::vector<Actor*>& inActorList) : actorList(inActorList)
    { // I'm setting values, but this sprite will never actually be drawn because it won't have an actor list.
        // position and rotation
        x = 100;
        y = 100;
        rotation = 0;
        rotationOffset = 0;

        // physics data

        velocityVec = Vector2D(0,0);
        accelerationVec = Vector2D(0,0);
        acceleration = 0;
        maxSpeed = 100;
        deceleration = 0;

        // sprite and hitbox
        spr = initSprite(0);
        hitbox = Rectangle(x, y, spr->spr.image.subtex->width, spr->spr.image.subtex->height);
    }
    Actor(float inX, float inY, float index, std::vector<Actor*>& inActorList) : actorList(inActorList)
    {
        x = inX;
        y = inY;
        rotation = 0;
        rotationOffset = 0;
        spr = initSprite(index);
        hitbox = Rectangle(x, y, spr->spr.image.subtex->width, spr->spr.image.subtex->height);

        actorList.push_back(this);
    }

    virtual void act(float dt)
    {
        alignHitbox();
    }

    void alignHitbox()
    {
        hitbox.x = x - hitbox.width/2;
        hitbox.y = y - hitbox.height/2;
    }

    void scaleHitbox(float scalar)
    {
        hitbox.x *= scalar;
        hitbox.y *= scalar;
        hitbox.width *= scalar;
        hitbox.height *= scalar;
    }

    virtual void dispose()
    {
        actorList.erase(std::remove(actorList.begin(), actorList.end(), this), actorList.end());
    }

    virtual void draw()
    {
        C2D_SpriteSetPos(&spr->spr, x, y);
        C2D_SpriteSetRotationDegrees(&spr->spr, rotation + rotationOffset);
        C2D_DrawSprite(&spr->spr);
    }

    // PHYSICS
    void accelerateAtAngle(float angle)
    {
        accelerationVec.add( Vector2D(acceleration, 0).setAngleDeg(angle) );
    }

    void accelerateForward()
    {
        accelerateAtAngle( rotation );
    }

    void moveBy (float inX, float inY) 
    {
		if (inX != 0 || inY != 0) 
        {
			x += inX;
			y += inY;
		}
	}

    void applyPhysics(float dt) /// borrowed from my college class' BaseActor code
    {
        // apply acceleration
        velocityVec.add( accelerationVec.x * dt, accelerationVec.y * dt );

        float speed = velocityVec.len();

        // decrease speed (decelerate) when not accelerating
        if (accelerationVec.len() < 0.0001f)
            speed -= deceleration * dt;

        // keep speed within set bounds
        speed = clamp(speed, 0, maxSpeed);

        // update velocity
        if (speed == 0)
            velocityVec.set(speed, 0);
        else
            velocityVec.setLength(speed);

        // update position according to value stored in velocity vector
        moveBy( velocityVec.x * dt, velocityVec.y * dt );

        // reset acceleration
        accelerationVec.set(0,0);
    }

    // MISC
    void wrapAroundWorld()
    {
        if(y - hitbox.height > SCREEN_HEIGHT)
            y = -hitbox.height;
        if(y < -hitbox.height)
            y = SCREEN_HEIGHT + hitbox.height;
        if(x - hitbox.width > SCREEN_WIDTH)
            x = -hitbox.width;
        if(x < -hitbox.width)
            x = SCREEN_WIDTH + hitbox.width;
    }
};