#include "essential.hpp"

#pragma once

class Paddle
{
protected:
	float y = 0;
public:
	Paddle();

	Paddle(float inY);

	float getY();

	void move(float inY, float dt);
};