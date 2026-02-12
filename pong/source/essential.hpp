#pragma once

class Vector2D
{
public:
	float x;
	float y;
	Vector2D()
	{
		x = 0;
		y = 0;
	}
	Vector2D(float inX, float inY)
	{
		x = inX;
		y = inY;
	}
};

class Rectangle
{
public:
	float x;
	float y;
	float width;
	float height;
	Rectangle()
	{
		x = 0;
		y = 0;
		width = 1;
		height = 1;
	}
	Rectangle(float inX, float inY, float inWidth, float inHeight)
	{
		x = inX;
		y = inY;
		width = inWidth;
		height = inHeight;
	}
};