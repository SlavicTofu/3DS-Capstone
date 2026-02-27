#include "essential.hpp"

#pragma once

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 400
#define PADDLE_WIDTH 5
#define PADDLE_HEIGHT 40
#define BALL_RADIUS 5
#define HIT_MULTIPLIER 1.1
#define CPU_FOLLOW_DISTANCE 20
#define PADDLE_MARGIN 10
#define CPU_SPEED 80
#define PLAYER_SPEED 100


enum GAME_STATE
{
	MENU,
	IN_GAME,
	EXIT
};

// Delta time

static u64 lastTick = 0;

void initTime()
{
    lastTick = svcGetSystemTick();
}

float getDeltaTime()
{
    u64 currentTick = svcGetSystemTick();
    u64 diffTick = currentTick - lastTick;
    lastTick = currentTick;

    const float tickFrequency = 268435456.0f; // convert ticks to seconds
    float deltaTime = (float)diffTick / tickFrequency;

    return deltaTime;
}

void drawCircle(Vector2D position, float radius, u32 color)
{
    float x = position.x;
    float y = position.y;
    C2D_DrawCircleSolid(x, y, 0, radius, color);
}

void drawPaddle(float x, float y, float height, u32 color)
{
	C2D_DrawRectangle(x, y, 0, PADDLE_WIDTH, height, color, color, color, color);
}

class Paddle
{
protected:
	float y = 0;
public:
	Paddle()
	{
		y = 0;
	}
	Paddle(float inY)
	{
		y = inY;
	}
	float getY()
	{
		return y;
	}
	void move(float inY, float dt)
	{
		float tempY = y;
		tempY += inY * dt;

		if(tempY + PADDLE_HEIGHT > SCREEN_HEIGHT)
			tempY = SCREEN_HEIGHT - PADDLE_HEIGHT;
		else if (tempY < 0)
			tempY = 0;

		y = tempY;
	}
};

class Ball
{
private:
	Vector2D m_position;
	float m_radius;
	Vector2D m_velocity;
public:
	Ball()
	{
		m_position = Vector2D(0,0);
		m_radius = 5;
		m_velocity = Vector2D(0,0);
	}
	Ball(Vector2D position, float radius)
	{
		m_position = position;
		m_radius = radius;
		m_velocity = Vector2D(-50,100);
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
	void reset()
	{
		m_position.x = SCREEN_WIDTH/2;
		m_position.y = SCREEN_HEIGHT/2;

		m_velocity = Vector2D(0,0);
	}
	void hitWall()
	{
		m_velocity.y *= -1;
	}
	void hitPaddle(Paddle paddle)
	{
		m_velocity.x *= -1.05;

	}
	void applyPhysics(float dt)
	{
		m_position.y += m_velocity.y * dt;
		m_position.x += m_velocity.x * dt;
	}
};

class PongGame
{
private:
	Ball ball;
    Paddle player;
    Paddle cpu;
    C3D_RenderTarget* top;
    u32 clrClear, clrBlue, clrWhite, clrRed;
public:
	PongGame(const Ball& inBall, const Paddle& inPlayer, const Paddle& inCPU, C3D_RenderTarget* inTop, u32 clear, u32 blue, u32 white, u32 red) // passing by reference is a good idea? i will want guidance on this
	{
		ball = inBall;
		player = inPlayer;
		cpu = inCPU;
		top = inTop;
		clrClear = clear;
		clrBlue = blue;
		clrRed = red;
		clrWhite = white;
	}

	bool exitGame = false;

	void handleInput(float dt)
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START)
			exitGame = true; // break in order to return to hbmenu

		if (kHeld & KEY_CPAD_UP )
			player.move(-PLAYER_SPEED, dt);
		else if (kHeld & KEY_CPAD_DOWN)
			player.move(PLAYER_SPEED, dt);
	}
	void update(float dt)
	{
		float ballX = ball.getPosition().x;
		float ballY = ball.getPosition().y;
		float ballR = ball.getRadius();

		// ball logic
		if (ballX < PADDLE_MARGIN || ballX > SCREEN_WIDTH - PADDLE_MARGIN)
		{
			ball.reset();
		}
		else if (ballX - ballR < PADDLE_MARGIN + PADDLE_WIDTH && ballY > player.getY() - ballR && ballY < player.getY() + PADDLE_HEIGHT + ballR) // contact with player
			ball.hitPaddle(player);

		else if (ballX + ballR > SCREEN_WIDTH - PADDLE_MARGIN && ballY > cpu.getY() - ballR && ballY < cpu.getY() + PADDLE_HEIGHT + ballR) // contact with cpu
			ball.hitPaddle(cpu);

		if (ballY - ballR <= 0 || ballY + ballR > SCREEN_HEIGHT) // hit walls
			ball.hitWall();

		ball.applyPhysics(dt);

		// cpu logic
		float cpuY = cpu.getY();
		float ballVX = ball.getVelocity().x;
		float distance = std::abs(ballY - (cpuY + PADDLE_HEIGHT / 2));
		if (ballX > SCREEN_WIDTH/2 && ballVX > 0 && distance > CPU_FOLLOW_DISTANCE)
		{
			if (ballY > cpuY + PADDLE_HEIGHT / 2)
			{
				cpu.move(CPU_SPEED, dt);
			}
			else
			{
				cpu.move(-CPU_SPEED, dt);
			}
		}
	}
	void render()
	{
		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);
		
		// Draw the things to render
		drawCircle(ball.getPosition(), ball.getRadius(), clrBlue); // Ball
		drawPaddle(PADDLE_MARGIN, player.getY(), PADDLE_HEIGHT, clrWhite); // Player
		drawPaddle(SCREEN_WIDTH - PADDLE_MARGIN, cpu.getY(), PADDLE_HEIGHT, clrRed); // CPU
		C3D_FrameEnd(0);
	}
};