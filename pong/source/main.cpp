#include <citro2d.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <3ds.h>

#include "essential.hpp"
#include "pong.hpp"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

int main(int argc, char* argv[])
{
	// Init GFX
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);
	initTime();

	// Create pong game
	PongGame Game = PongGame(
		Ball(Vector2D(SCREEN_WIDTH/2, SCREEN_HEIGHT/2), 5),
		Paddle(SCREEN_HEIGHT/2), // player
		Paddle(SCREEN_HEIGHT/2), // cpu
		C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT), // screen
		C2D_Color32(0x00, 0x00, 0x00, 0xFF), // black
		C2D_Color32(0x9f, 0xc5, 0xe8, 0xFF), // blue
		C2D_Color32(0xac, 0xfc, 0x79, 0xFF), // green
		C2D_Color32(0xFF, 0x00, 0x00, 0xFF) // red
	);

	// Main loop
	
	while (aptMainLoop())
	{
		if(Game.exitGame) break;

		float dt = getDeltaTime();

		Game.handleInput(dt);
		Game.update(dt);
		Game.render();
	}

	//Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}