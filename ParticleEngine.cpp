#include "ParticleEngine.h"

class ParticleEngine{
private:
	std::vector<Particle*> particles;
	float direction;
	float spreadAngle;
	uint8_t minSpeed;
	uint8_t maxSpeed;
	uint16_t xSpawnRange;
	uint16_t ySpawnRange;
	uint16_t xPos;
	uint16_t yPos;
	uint16_t particleTTL;
	
ParticleEngine::ParticleEngine(float spread, uint16_t xRange, uint16_t yRange,
								uint8_t pMinSpeed, uint8_t pMaxSpeed, uint16_t TTL, uint8_t max){
	minSpeed = pMinSpeed;
	maxSpeed = pMaxSpeed;
	spreadAngle = spread;
	xSpawnRange = xRange;
	ySpawnRange = yRange;
	particleTTL = TTL;
	particles.reserve(max);
}	
ParticleEngine::~ParticleEngine(){
    for(std::vector<Particle*>::iterator it = particles.begin(); it!= particles.end(); ++it){
        if(*it != NULL){
            delete (*it);
        }
    }
}

void ParticleEngine::updatePosition(float newDirection, int newX, int newY){
	direction = newDirection;
	xPos = newX;
	yPos = newY;
}

void ParticleEngine::updateParticles(bool spawnNew, uint32_t delta){
	for(int i = 0; i < max; i++){
		if(particles.at(i) == NULL){
			if(spawnNew){
			//int x = xPos + rand()%(2*xSpawnRange+1) - xSpawnRange;
			//int y = yPos + rand()%(2*ySpawnRange+1) - ySpawnRange;
			//int vel = minSpeed + rand()%maxSpeed+1;
			//int dDir = 
			particles.push_back(new Particle(xPos, yPos, direction, 5, 20);
			}
		}
		else{
			particles.at(i)->moveObject(delta);
			particles.at(i)->renderParticle(screen);
		}
	}
}
