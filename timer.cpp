/*
 * timer.cpp
 *
 *  Created on: Jan 25, 2012
 *      Author: msegersten
 */

#include "timer.h"

Timer::Timer() {
    startTick = 0;
    pausedTick = 0;
    started = false;
    paused = false;
}

void Timer::start() {
    startTick = SDL_GetTicks();
    started = true;
    paused = false;
}

void Timer::stop() {
    startTick = 0;
    pausedTick = 0;
    started = false;
    paused = false;
}

void Timer::pause() {
    if (started && !paused) {
        paused = true;
        pausedTick = SDL_GetTicks() - startTick;
    }
}

void Timer::unpause() {
    if (paused) {
        paused = false;
        startTick = SDL_GetTicks() - pausedTick;
        pausedTick = 0;
    }
}

bool Timer::is_paused() {
    return paused;
}

bool Timer::is_started() {
    return started;
}

int Timer::get_ticks() {
    if (started) {
        if (paused) {
            return pausedTick;
        } else {
            return (SDL_GetTicks() - startTick);
        }
    } else
        return 0;
}


