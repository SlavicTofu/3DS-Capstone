#include <citro2d.h>
#include <3ds.h>
#include "essential.hpp"

#pragma once

static C2D_SpriteSheet spriteSheet;

void setupSprite(C2D_Sprite* spr, int index) {
    C2D_SpriteFromSheet(spr, spriteSheet, index);
}
