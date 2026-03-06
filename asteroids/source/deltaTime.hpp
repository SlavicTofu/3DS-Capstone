#include <3ds.h>

#pragma once

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