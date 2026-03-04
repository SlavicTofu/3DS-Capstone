#include "essential.hpp"
#include "paddle.h"

#define SCREEN_HEIGHT 240
#define PADDLE_HEIGHT 40

Paddle::Paddle()
{
	y = 0;
}
Paddle::Paddle(float inY)
{
	y = inY;
}
float Paddle::getY()
{
	return y;
}
void Paddle::move(float inY, float dt)
{
	float tempY = y;
	tempY += inY * dt;

	if(tempY + PADDLE_HEIGHT > SCREEN_HEIGHT)
		tempY = SCREEN_HEIGHT - PADDLE_HEIGHT;
	else if (tempY < 0)
		tempY = 0;

	y = tempY;
}