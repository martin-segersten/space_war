/*
 * timer.h
 *
 *  Created on: Jan 25, 2012
 *      Author: msegersten
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <stdint.h>
#include "SDL/SDL.h"

class Timer {
private:
    uint32_t startTick;
    uint32_t pausedTick;
    bool started;
    bool paused;

public:
    Timer();
    void start();
    void stop();
    void pause();
    void unpause();
    int get_ticks();
    bool is_started();
    bool is_paused();
};



#endif /* TIMER_H_ */
