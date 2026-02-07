/* 
 * Contains helper functions which will work to abstract the game code
 * from the 3DS-specific graphics code, which will make it easier to
 * build the project for other devices.
 */

#include "essential.hpp"

#include <citro2d.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <3ds.h>


#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

u32 clrWhite;
u32 clrGreen;
u32 clrRed;
u32 clrBlue;

void initGfx() // code copied from 3ds-examples
{
    gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);

	// Create colors
	clrWhite = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
	clrGreen = C2D_Color32(0x00, 0xFF, 0x00, 0xFF);
	clrRed   = C2D_Color32(0xFF, 0x00, 0x00, 0xFF);
	clrBlue  = C2D_Color32(0x00, 0x00, 0xFF, 0xFF);
}

void render() {}

void drawCircle(Vector2D position, float radius)
{
    float x = position.x;
    float y = position.y;
    C2D_DrawCircleSolid(x, y, 0, radius, clrWhite);
}