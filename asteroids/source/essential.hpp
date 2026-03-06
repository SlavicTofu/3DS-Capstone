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
	float x, y, width, height;

	Rectangle()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
	}
	Rectangle(float inX, float inY, float inWidth, float inHeight)
	{
		x = inX;
		y = inY;
		width = inWidth;
		height = inHeight;
	}

	bool overlaps (Rectangle r) // ripped straight from LibGDX's Rectangle.java
	{
		return x < r.x + r.width && x + width > r.x && y < r.y + r.height && y + height > r.y;
	}
};

typedef struct
{
	C2D_Sprite spr;
	float x, y, rotation;
} Sprite;