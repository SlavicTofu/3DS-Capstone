#include "essential.hpp"
#include "paddle.h"

#define SCREEN_HEIGHT 240

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
float Paddle::getHeight()
{
	return height;
}
float Paddle::getWidth()
{
	return width;
}
void Paddle::move(float inY, float dt)
{
	float tempY = y;
	tempY += inY * dt;

	if(tempY + height > SCREEN_HEIGHT)
		tempY = SCREEN_HEIGHT - height;
	else if (tempY < 0)
		tempY = 0;

	y = tempY;
}