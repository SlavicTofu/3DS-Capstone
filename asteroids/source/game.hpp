#include <vector>
#include <3ds.h>
#include "actor.hpp"
#include "player.hpp"
#include "asteroid.hpp"
#include "laser.hpp"
#include "essential.hpp"

#pragma once

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 400
#define MAX_ACTORS 10

enum GAME_STATE
{
	MENU,
	IN_GAME,
	EXIT
};

u32 clrClear = C2D_Color32(0x00, 0x00, 0x00, 0x00);

// Game

class AsteroidsGame
{
private:
    C3D_RenderTarget* top;
	std::vector<Actor*> actors{};
	std::vector<Asteroid*> asteroids{};
	std::vector<Laser*> lasers{};
public:
	AsteroidsGame(C3D_RenderTarget* inTop)
	{
		top = inTop;
		initialize();
	}

	bool exitGame = false;

	// declare backdrop and player

	Actor* backdrop = new Actor(0, 0, 4);
	Player* player = new Player(300, 150);

	// declare ui elements

	
	

	void initialize()
	{
		addAsteroid(new Asteroid(200, 100, 1, rand() % 361));

	}

	// Adding and disposing actors, maintaining actor lists

	void addActor(Actor* actor)
	{
		actors.push_back(actor);
	}

	void dispose(Actor* actor)
    {
        actors.erase(std::remove(actors.begin(), actors.end(), actor), actors.end());
		delete actor;
    }

	void addAsteroid(Asteroid* asteroid)
	{
		addActor(asteroid);
		asteroids.push_back(asteroid);
	}

	void disposeAsteroid(Asteroid* asteroid)
	{
		asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroid), asteroids.end());
		dispose(asteroid);
	}

	void addLaser(Laser* laser)
	{
		addActor(laser);
		lasers.push_back(laser);
	}

	void disposeLaser(Laser* laser)
	{
		lasers.erase(std::remove(lasers.begin(), lasers.end(), laser), lasers.end());
		dispose(laser);
	}

	// game lifecycle

	void handleInput(float dt)
	{
		hidScanInput();

		circlePosition pos;

		//Read the CirclePad position
		hidCircleRead(&pos);

		// Respond to user input
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START)
			exitGame = true; // to return to hbmenu

		player->handleInput(dt, kDown, kHeld, pos);

		if(kDown & KEY_A)
		{
			printf("Actors List has %i", actors.size());
		}
		
	}
	void update(float dt)
	{
		// player acts

		player->act(dt);

		if (player->shooting)
		{
			player->shooting = false;
			addLaser(new Laser(player->x, player->y, player->rotation));
		}

		// collisions and stuff

		for(Laser* laser : lasers)
		{
			if(!laser->overlaps(backdrop))
			{
				disposeLaser(laser);
			}
			else
			{
				for(Asteroid* asteroid : asteroids)
				{
					if(laser->overlaps(asteroid))
					{
						disposeLaser(laser);
						if(asteroid->stage <= 3)
						{
							int randInt = rand() % 361;
							addAsteroid(new Asteroid(asteroid->x, asteroid->y, asteroid->stage+1, randInt));
							addAsteroid(new Asteroid(asteroid->x, asteroid->y, asteroid->stage+1, randInt + randInt));
						}
						disposeAsteroid(asteroid);
					}
				}
			}
		}

		for(Asteroid* asteroid : asteroids)
		{
			if(player->overlaps(asteroid))
			{

			}
		}

		// actors act
		for( Actor* actor : actors )
		{
			actor->act(dt);
		}
	}
	void render()
	{
		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);
		
		// Draw the things to render

		backdrop->draw();

		for( Actor* actor : actors )
		{
			actor->draw();
			C2D_DrawRectSolid(actor->hitbox.x, actor->hitbox.y, 0, actor->hitbox.width, actor->hitbox.height, C2D_Color32(0xff, 0x00, 0x00, 0x88));
		}

		player->draw();

		// draw ui



		C2D_DrawRectSolid(player->hitbox.x, player->hitbox.y, 0, player->hitbox.width, player->hitbox.height, C2D_Color32(0x8B, 0xFF, 0xA8, 0x88));

		C3D_FrameEnd(0);
	}
};