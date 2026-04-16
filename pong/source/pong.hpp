#include "essential.hpp"
#include "paddle.h"
#include "ball.h"

#pragma once

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 400
#define PADDLE_WIDTH 5
#define HIT_MULTIPLIER 1.1
#define CPU_FOLLOW_DISTANCE 10
#define PADDLE_MARGIN 10
#define CPU_SPEED 105
#define PLAYER_SPEED 120
#define BALL_STARTING_SPEED 80


enum GAME_STATE
{
	MENU,
	PLAYER_SERVE,
	CPU_SERVE,
	PLAY
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

// Drawing

void drawCircle(Vector2D position, float radius, u32 color)
{
    float x = position.x;
    float y = position.y;
    C2D_DrawCircleSolid(x, y, 0, radius, color);
}

void drawPaddle(float x, float y, float height, u32 color)
{
	C2D_DrawRectSolid(x, y, 0, PADDLE_WIDTH, height, color);
}

// Game

class PongGame
{
private:
	Ball ball;
    Paddle player;
    Paddle cpu;
    C3D_RenderTarget* top;
    u32 clrClear, clrBlue, clrWhite, clrRed;

	int playerScore = 0, cpuScore = 0;
	bool scoreMade = true;
	GAME_STATE gameState = CPU_SERVE;
public:
	PongGame(Ball inBall, Paddle inPlayer, Paddle inCPU, C3D_RenderTarget* inTop, u32 clear, u32 blue, u32 white, u32 red)
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
		float ballR = ball.getRadius();

		if(gameState == PLAY)
		{
			float ballX = ball.getPosition().x;
			float ballY = ball.getPosition().y;

			// ball logic
			if ((ballX < PADDLE_MARGIN || ballX > SCREEN_WIDTH - PADDLE_MARGIN) && !scoreMade) // scoring
			{
				scoreMade = true;
				if(ballX > SCREEN_WIDTH/2) // CPU side
				{
					playerScore++;
					gameState = PLAYER_SERVE;
				}
				else // player side
				{
					cpuScore++;
					gameState = CPU_SERVE;
				}
			}
			else if (ballX - ballR < PADDLE_MARGIN + player.getWidth() &&
					ballY > player.getY() - ballR &&
					ballY < player.getY() + player.getHeight() + ballR) // contact with player
				ball.hitPaddle(player);

			else if (ballX + ballR > SCREEN_WIDTH - PADDLE_MARGIN &&
					ballY > cpu.getY() - ballR &&
					ballY < cpu.getY() + cpu.getHeight() + ballR) // contact with cpu
				ball.hitPaddle(cpu);

			if (ballY - ballR <= 0 || ballY + ballR > SCREEN_HEIGHT) // hit walls
				ball.hitWall();

			ball.applyPhysics(dt);

			// cpu logic
			float cpuY = cpu.getY();
			float ballVX = ball.getVelocity().x;
			float ballVY = ball.getVelocity().y;
			float distance = ballY + ballVY * 0.3 - (cpuY + cpu.getHeight() / 2);

			if (ballX > SCREEN_WIDTH/2 && ballVX > 0 && (distance > CPU_FOLLOW_DISTANCE || distance < -CPU_FOLLOW_DISTANCE))
			{
				cpu.move(CPU_SPEED * distance * 0.02f, dt);
			}
		}
		else if (gameState == PLAYER_SERVE)
		{
			scoreMade = false;
			ball.setVelocity(-BALL_STARTING_SPEED, (rand() % 201) - 100);
			ball.setPosition(SCREEN_WIDTH/2, player.getY()-player.getHeight()/2);
			gameState = PLAY;
		}
		else if (gameState == CPU_SERVE)
		{
			scoreMade = false;
			ball.setVelocity(BALL_STARTING_SPEED, (rand() % 201) - 100);
			ball.setPosition(SCREEN_WIDTH/2, player.getY()-player.getHeight()/2);
			gameState = PLAY;
		}
	}
	void render()
	{
		// Start Render
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);
		
		// Render Text
		printf("\x1b[2;1HPlayer Score: %i\nCPU Score: %i\x1b[K", playerScore, cpuScore);

		// Draw the things to render
		drawCircle(ball.getPosition(), ball.getRadius(), clrBlue); // Ball
		drawPaddle(PADDLE_MARGIN, player.getY(), player.getHeight(), clrWhite); // Player
		drawPaddle(SCREEN_WIDTH - PADDLE_MARGIN, cpu.getY(), cpu.getHeight(), clrRed); // CPU
		C3D_FrameEnd(0);
	}
};