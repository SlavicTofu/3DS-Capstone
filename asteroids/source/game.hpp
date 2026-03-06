#include <vector>
#include <3ds.h>
#include "actor.hpp"
#include "player.hpp"
#include "asteroid.hpp"
#include "spriteHandler.hpp"
#include "essential.hpp"

#pragma once

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 400
#define MAX_ACTORS 40

enum GAME_STATE
{
	MENU,
	IN_GAME,
	EXIT
};

u32 clrClear = C2D_Color32(0x00, 0x00, 0x00, 0x00);

std::vector<Actor*> actors{};

// Game

class AsteroidsGame
{
private:
    C3D_RenderTarget* top;
public:
	AsteroidsGame(C3D_RenderTarget* inTop)
	{
		top = inTop;
		initialize();
	}

	bool exitGame = false;

	void handleInput(float dt)
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START)
			exitGame = true; // to return to hbmenu

		
	}
	void initialize()
	{
		actors.push_back(new Actor(100, 100, 0));
		actors.push_back(new Player(300, 150, 2));
		actors.push_back(new Asteroid(200, 100, 5));

	}
	void update(float dt)
	{
		for( Actor* actor : actors )
		{
			C2D_SpriteSetPos(&actor->spr->spr, actor->x, actor->y);
			
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
		
		for( Actor* actor : actors )
		{
			C2D_DrawSprite(&actor->spr->spr);
		}

		C3D_FrameEnd(0);
	}
};