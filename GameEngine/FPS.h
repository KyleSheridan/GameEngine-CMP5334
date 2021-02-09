#pragma once

#include <string>
#include <SDL.h>
#include <iostream>

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
    Uint32 frametimes[FRAME_VALS];

    // var to store result in ticks for curr frame - SDL_GetTicks()
    Uint32 frametimelast;

    Uint32 framecount;

    float framespersecond;

    float lastFrameTime;

    float deltaTime;
};