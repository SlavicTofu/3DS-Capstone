#include "essential.hpp"

#pragma once

enum GAME_STATE
{
	MENU,
	IN_GAME,
	EXIT
};

enum PLAY_STATE
{
	SERVE_PLAYER_ONE,
	SERVE_PLAYER_TWO,
	TOWARD_PLAYER_ONE,
	TOWARD_PLAYER_TWO
};

class Court
{
private:
	Rectangle dimensions;
public:
	Court(Rectangle dims)
	{
		dimensions = dims;
	}
	Rectangle getDimensions()
	{
		return dimensions;
	}
};

class Paddle
{
private:
	Rectangle m_rect;
public:
	Paddle(Rectangle rect)
	{
		m_rect = rect;
	}
	Rectangle getPositionSize()
	{
		return m_rect;
	}
	void setPositionSize(Rectangle rect)
	{
		m_rect = rect;
	}
	void setPosition(Vector2D newPos)
	{
		m_rect.x = newPos.x;
		m_rect.y = newPos.y;
	}
};

class Ball
{
private:
	Vector2D m_position;
	float m_radius;
	Vector2D m_velocity;
public:
	Ball(Vector2D position, float radius)
	{
		m_position = position;
		m_radius = radius;
		m_velocity = Vector2D(0,0);
	}
	Vector2D getPosition()
	{
		return m_position;
	}
	float getRadius()
	{
		return m_radius;
	}
	Vector2D getVelocity()
	{
		return m_velocity;
	}
	void setPosition(Vector2D position)
	{
		m_position = position;
	}
	void setVelocity(Vector2D velocity)
	{
		m_velocity = velocity;
	}
};