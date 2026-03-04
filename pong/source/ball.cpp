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
void Ball::reset()
{
	m_position.x = SCREEN_WIDTH/2;
	m_position.y = SCREEN_HEIGHT/2;

	m_velocity = Vector2D(0,0);
}
void Ball::hitWall()
{
	m_velocity.y *= -1;
}
void Ball::hitPaddle(Paddle paddle)
{
	m_velocity.x *= -1.05;

	float distToCenter = paddle.getY() - m_position.y;
	
	if( distToCenter < 15 && distToCenter > 5 ) // 1st 'rung' positive
		m_velocity.y -= 10;
	else if( distToCenter > -15 && distToCenter < -5 ) // 1st 'rung' negative
		m_velocity.y += 10;
	else if( distToCenter < 30 && distToCenter > 15 ) // 2nd 'rung' positive
		m_velocity.y -= 30;
	else if( distToCenter > -30 && distToCenter < -15 ) // 2nd 'rung' negative
		m_velocity.y += 30;
	else if( distToCenter < 60 && distToCenter > 30 ) // 3rd 'rung' positive
		m_velocity.y -= 90;
	else if( distToCenter > -60 && distToCenter < -30 ) // 3rd 'rung' negative
		m_velocity.y += 90;
}
void Ball::applyPhysics(float dt)
{
	m_position.y += m_velocity.y * dt;
	m_position.x += m_velocity.x * dt;
}