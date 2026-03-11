#include "essential.hpp"

#pragma once

class Paddle
{
protected:
	float y = 0;
	int height = 40, width = 5;
public:
	Paddle();

	Paddle(float inY);

	float getY();

	float getHeight();

	float getWidth();

	void move(float inY, float dt);
};