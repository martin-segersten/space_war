#include "Particle.h"


Particle::Particle(int x, int y, double direction, int speed, int TTL){
    xPos = x;
    yPos = y;
    xVel = cos(direction) * speed;
    yVel = sin(direction) * speed;
    distance = 0;
    alive = true;
    ttl = TTL;
}

void Particle::renderParticle(SDL_Surface * screen){
    SDL_Rect temp;
    temp.w = 1;
    temp.h = 1;
    temp.x = (int) xPos;
    temp.y = (int) yPos;
    SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
}

void Particle::moveObject(uint32_t delta){
    if(distance > PARTICLE_TTL)
        alive = false;
    else{
        xPos += xVel * delta/1000.f;
        yPos += xVel * delta/1000.f;
    }
}

bool Particle::isAlive(){
	return alive;
}
