#pragma once

#include <string>
#include "CrossPlatform.h"
#include <iostream>
#include <cstring>

#define FRAME_VALS 10

class FPS {
public:
    FPS();

    void init();
    void update();

    const float getDeltaTime() {
        return deltaTime;
    }

    const float getFPS() {
        return framespersecond;
    }

private:
    // array to store the frame times
    uint32_t frametimes[FRAME_VALS];

    // var to store result in ticks for curr frame - SDL_GetTicks()
    uint32_t frametimelast;

    uint32_t framecount;

    float framespersecond;

    float lastFrameTime;

    float deltaTime;
};