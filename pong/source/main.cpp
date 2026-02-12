#include <citro2d.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <3ds.h>

#include "essential.hpp"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

void processInput(u32 kDown)
{
	// input processing
}

void drawCircle(Vector2D position, float radius, u32 color)
{
    float x = position.x;
    float y = position.y;
    C2D_DrawCircleSolid(x, y, 0, radius, color);
}

int main(int argc, char* argv[])
{
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	// Create colors
	u32 clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	u32 clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
	u32 clrRed = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	u32 clrBlue = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
	u32 clrClear = C2D_Color32(0xFF, 0xD8, 0xB0, 0x68);

	Vector2D circlePos = Vector2D(200, 120);
	// Main loop
	
	while (aptMainLoop())
	{
		hidScanInput();

		// Respond to user input
		u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
		if (kHeld & KEY_CPAD_RIGHT)
			circlePos.x += 1;
		else if (kHeld & KEY_CPAD_LEFT)
			circlePos.x -= 1;
		if (kHeld & KEY_CPAD_UP)
			circlePos.y -= 1;
		else if (kHeld & KEY_CPAD_DOWN)
			circlePos.y += 1;

		// Render the scene
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, clrClear);
		C2D_SceneBegin(top);
	   
		// Draw the things to render
		drawCircle(circlePos, 20, clrBlue);

	    C3D_FrameEnd(0);
	}

	//Deinit libs
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}