#include <cmath>

#pragma once

static float pi = 2*asin(1.0);
static float degreesToRadians = pi / 180;

static float clamp (float value, float min, float max)
{
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

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
	void add(Vector2D v)
	{
		x += v.x;
		y += v.y;
	}
	void add(float inX, float inY)
	{
		x += inX;
		y += inY;
	}
	void set(float inX, float inY)
	{
		x = inX;
		y = inY;
	}
	float len()
	{
		return sqrt(x*x + y*y);
	}
	Vector2D scl (float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	Vector2D setLength (float len)
	{
		float oldLen2 = x * x + y * y;
		float len2 = len * len;

		return (oldLen2 == 0 || oldLen2 == len2) ? *this : scl((float)sqrt(len2 / oldLen2));
	}
	Vector2D setAngleDeg (float degrees)
	{
		float radians = degrees * degreesToRadians;
		x = len();
		y = 0;

		float cos = std::cos(radians);
		float sin = std::sin(radians);

		float newX = x * cos - y * sin;
		float newY = x * sin + y * cos;

		x = newX;
		y = newY;

		return *this;
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