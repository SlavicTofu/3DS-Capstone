#include <citro2d.h>
#include <3ds.h>
#include "essential.hpp"

#define MAX_SPRITES 40

#pragma once

static C2D_SpriteSheet spriteSheet;
static Sprite sprites[MAX_SPRITES];
int numSprites = 0;

Sprite* initSprite(int index)
{
	Sprite* sprite = &sprites[numSprites];
	numSprites++;
	C2D_SpriteFromSheet(&sprite->spr, spriteSheet, index);
    return sprite;
}