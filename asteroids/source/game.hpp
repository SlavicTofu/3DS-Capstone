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
#define SPAWN_DISTANCE 100

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

	// declare backdrop and player

	Actor* backdrop = new Actor(0, 0, 4);
	Player* player = new Player(300, 150);

	// declare ui elements

	int ui_x = 188;
	int ui_y = 195;

	Actor* ui_elements[6] =
	{
		new Actor(ui_x, ui_y, 16),
		new Actor(ui_x + 16, ui_y, 16),
		new Actor(ui_x + 32, ui_y, 16),
		new Actor(ui_x, ui_y, 15),
		new Actor(ui_x + 16, ui_y, 15),
		new Actor(ui_x + 32, ui_y, 15)
	};

	// declare game variables

	int player_health = 3;
	bool game_over = false;

public:
	AsteroidsGame(C3D_RenderTarget* inTop)
	{
		top = inTop;
		initialize();
	}

	bool exitGame = false;

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

	// asteroid spawner
	void spawnAsteroid()
	{
		bool spawnValid = false;
		float spawnX, spawnY;
		do
		{
			spawnX = rand() % SCREEN_WIDTH;
			spawnY = rand() % SCREEN_HEIGHT;

			Rectangle spawnValidityHitbox = 
			Rectangle(spawnX - SPAWN_DISTANCE/2,
					  spawnY - SPAWN_DISTANCE/2,
					  SPAWN_DISTANCE,
					  SPAWN_DISTANCE);
			
			spawnValid = !player->overlaps(spawnValidityHitbox);

		} while (!spawnValid);

		addActor(new Asteroid(spawnX, spawnY, 1, rand() % 361));
	}

	// handle Game Over
	void gameOver()
	{
		for(Actor* actor : actors)
		{
			dispose(actor);
		}
		delete player;

		addActor(new Actor((SCREEN_WIDTH/2) - 47, (SCREEN_HEIGHT/2) - 23, 17));
	}

	// game lifecycle

	void initialize()
	{
		for( int i = 1; i <= 4; i++ )
		{
			spawnAsteroid();
		}
	}

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

		if(!game_over) player->handleInput(dt, kDown, kHeld, pos);
		
	}

	void update(float dt)
	{
		if (!game_over)
		{
			// player acts

			player->act(dt);

			if (player->shooting)
			{
				player->shooting = false;
				addActor(new Laser(player->x, player->y, player->rotation));
			}

			// collisions
			checkCollisions();

			// actors act
			for( Actor* actor : actors )
			{
				actor->act(dt);
			}
			if(player_health <= 0)
			{
				game_over = true;
				gameOver();
			}
		}
	}

	void checkCollisions()
	{
		for( Actor* actor1 : actors )
		{
			if(actor1->type == ASTEROID && actor1->overlaps(player))
				handleCollisions(actor1, player);

			for ( Actor* actor2 : actors )
			{
				if(actor1->overlaps(actor2))
					handleCollisions(actor1, actor2);
			}
		}
	}

	void handleCollisions(Actor* actor1, Actor* actor2)
	{
		if(actor1->type == LASER && !actor1->overlaps(backdrop))
		{
			if( ((Laser*)actor1)->lifeTime <= 0 )
			{
				dispose(actor1);
			}
		}
		else if(actor1->type == LASER && actor2->type == ASTEROID)
		{
			dispose(actor1);
			if( ((Asteroid*)actor2)->stage <= 3)
			{
				int randInt = rand() % 361;
				addActor(new Asteroid(actor2->x, actor2->y, ((Asteroid*)actor2)->stage+1, randInt));
				addActor(new Asteroid(actor2->x, actor2->y, ((Asteroid*)actor2)->stage+1, randInt + randInt));
			}
			dispose(actor2);
		}

		if(actor1->type == ASTEROID && actor2->type == PLAYER && player->iTime <= 0)
		{
			if( ((Asteroid*)actor1)->stage <= 3)
			{
				int randInt = rand() % 361;
				addActor(new Asteroid(actor1->x, actor1->y, ((Asteroid*)actor1)->stage+1, randInt));
				addActor(new Asteroid(actor1->x, actor1->y, ((Asteroid*)actor1)->stage+1, randInt + randInt));
			}

			dispose(actor1);
			if(player_health >= 1) player_health -= 1;
			player->iTime = 2;
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
		}

		if(!game_over) player->draw();

		// draw ui

		for( int i = 0; i <= 2; i++ )
		{
			ui_elements[i]->draw();
			if(i < player_health)
				ui_elements[i+3]->draw();
		}

		C3D_FrameEnd(0);
	}
};