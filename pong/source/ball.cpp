#include "essential.hpp"
#include "paddle.h"
#include "ball.h"

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 400

Ball::Ball()
{
	m_position = Vector2D(0,0);
	m_radius = 5;
	m_velocity = Vector2D(0,0);
}
Ball::Ball(Vector2D position, float radius)
{
	m_position = position;
	m_radius = radius;
	m_velocity = Vector2D(-50,100);
}
Vector2D Ball::getPosition()
{
	return m_position;
}
float Ball::getRadius()
{
	return m_radius;
}
Vector2D Ball::getVelocity()
{
	return m_velocity;
}
void Ball::setPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}
void Ball::setVelocity(float x, float y)
{
	m_velocity.x = x;
	m_velocity.y = y;
}
void Ball::hitWall()
{
	m_velocity.y *= -1;
}
void Ball::hitPaddle(Paddle paddle)
{
	m_velocity.x *= -1.05;

	float pHeight = paddle.getHeight();
	float distToCenter = (paddle.getY() + pHeight/2) - m_position.y;
	float rungSection = pHeight / 16;
	
	if( distToCenter < 3 * rungSection && distToCenter > rungSection ) // 1st 'rung' positive
	{
		m_velocity.y = -40;
	}
	else if( distToCenter > -3 * rungSection && distToCenter < -rungSection ) // 1st 'rung' negative
	{
		m_velocity.y = 40;
	}
	else if( distToCenter < 6 * rungSection && distToCenter > 3 * rungSection ) // 2nd 'rung' positive
	{
		m_velocity.y = -60;
	}
	else if( distToCenter > -6 * rungSection && distToCenter < -3 * rungSection ) // 2nd 'rung' negative
	{
		m_velocity.y = 60;
	}
	else if( distToCenter < 10 * rungSection && distToCenter > 6 * rungSection ) // 3rd 'rung' positive
	{
		m_velocity.y = -120;
	}
	else if( distToCenter > -10 * rungSection && distToCenter < -6 * rungSection ) // 3rd 'rung' negative
	{
		m_velocity.y = 120;
	}
}
void Ball::applyPhysics(float dt)
{
	m_position.y += m_velocity.y * dt;
	m_position.x += m_velocity.x * dt;
}