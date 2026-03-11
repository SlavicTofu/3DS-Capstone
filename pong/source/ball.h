#include "essential.hpp"
#include "paddle.h"

#pragma once

class Ball
{
private:
	Vector2D m_position;
	float m_radius;
	Vector2D m_velocity;
public:
	Ball();
    
	Ball(Vector2D position, float radius);

	Vector2D getPosition();

	float getRadius();

	Vector2D getVelocity();

	void setPosition(float x, float y);

	void setVelocity(float x, float y);

	void hitWall();

	void hitPaddle(Paddle paddle);

	void applyPhysics(float dt);
};