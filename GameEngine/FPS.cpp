#include "FPS.h"

FPS::FPS()
{
    std::memset(frametimes, 0, sizeof(frametimes));
    framecount = 0;
    framespersecond = 0;
    frametimelast = 0;
}

void FPS::init()
{
    frametimelast = SDL_GetTicks();
}

void FPS::update()
{
    Uint32 frametimesindex;
    Uint32 getticks;
    Uint32 count;

    frametimesindex = framecount % FRAME_VALS;

    getticks = SDL_GetTicks();

    frametimes[frametimesindex] = getticks - frametimelast;

    if (framecount > 0) {
        lastFrameTime = frametimelast;
    }

    frametimelast = getticks;

    if (framecount > 0) {
        deltaTime = (frametimelast - lastFrameTime) / 1000;
    }
    else {
        deltaTime = 1 / 60;
    }

    framecount++;

    if (framecount < FRAME_VALS) {
        count = framecount;
    }
    else {
        count = FRAME_VALS;
    }

    framespersecond = 0;
    for (int i = 0; i < count; i++) {
        framespersecond += frametimes[i];
    }
    framespersecond /= count;

    framespersecond = 1000.0f / framespersecond;
}
