/* 
 * File:   Particle.h
 * Author: martin
 *
 * Created on 15 February 2012, 09:35
 */

#ifndef PARTICLE_H_
#define	PARTICLE_H_
#include "SDL/SDL.h"

class Particle{
private:
    int xVel;
    int yVel;
    float xPos;
    float yPos;
    float distance;
    int ttl;
    bool alive;
public:
    Particle(int x, int y, double direction, int speed, int TTL);
    void renderParticle(SDL_Surface * screen);
    void moveObject(uint32_t delta);
    bool isAlive();
    
    
    /*
     Particles for player when accelerating
     Particles when player is hit?
     Particles when asteroid is hit
     */
};

#endif	/* PARTICLE_H */

