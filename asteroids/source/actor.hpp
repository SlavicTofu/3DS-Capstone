#include "essential.hpp"
#include "spriteHandler.hpp"
#include <algorithm>

#pragma once

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 400

enum ACTOR_TYPE
{
    BASE,
    PLAYER,
    ASTEROID,
    LASER
};

class Actor
{
public:
    float x, y, rotation, rotationOffset, acceleration, maxSpeed, deceleration;
    Vector2D velocityVec, accelerationVec;
    C2D_Sprite spr;
    Rectangle hitbox;
    ACTOR_TYPE type;

    Actor()
    { // I'm setting values, but this sprite will never actually be drawn because it won't have an actor list.
        // position and rotation
        x = 100;
        y = 100;
        rotation = 0;
        rotationOffset = 0;

        type = BASE;

        // physics data

        velocityVec = Vector2D(0,0);
        accelerationVec = Vector2D(0,0);
        acceleration = 0;
        maxSpeed = 100;
        deceleration = 0;

        // sprite and hitbox
        setupSprite(&this->spr, 0);
        hitbox = Rectangle(x, y, spr.image.subtex->width, spr.image.subtex->height);
    }
    Actor(float inX, float inY, int index)
    {
        x = inX;
        y = inY;
        rotation = 0;
        rotationOffset = 0;
        type = BASE;
        setupSprite(&this->spr, index);
        hitbox = Rectangle(x, y, spr.image.subtex->width, spr.image.subtex->height);
    }

    virtual ~Actor()
    {
        // nothing to add, but compiler was complaining
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

    virtual void draw()
    {
        C2D_SpriteSetPos(&this->spr, x, y);
        C2D_SpriteSetRotationDegrees(&this->spr, rotation + rotationOffset);
        C2D_DrawSprite(&this->spr);
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

    bool overlaps(Actor* actor)
    {
        return hitbox.overlaps(actor->hitbox);
    }

    bool overlaps(Rectangle rect)
    {
        return hitbox.overlaps(rect);
    }
};