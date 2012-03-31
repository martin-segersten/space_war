#ifndef PARTICLEENGINE_H_
#define	PARTICLEENGINE_H_

#include <cstdlib>
#include <vector>
#include "Particle.h"

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
public:
	ParticleEngine(float spread, uint16_t xRange, uint16_t yRange, uint8_t minSpeed, uint8_t maxSpeed;);
	~ParticleEngine();
	void updatePosition(float newDirection, int newX, int newY);
	void updateParticles();

#endif
