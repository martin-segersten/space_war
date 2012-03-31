/* 
 * File:   Player.h
 * Author: martin
 *
 * Created on 07 February 2012, 01:28
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include <cmath>
#include "SDL/SDL.h"
#include "SDL/SDL_rotozoom.h"
#include "general.h"

#define MAX_BULLETS 5
#define INVIS_TIME 3
#define EXPLO_TIME 3
#define LEFT 1
#define RIGHT -1
#define ACC_RATE 250
#define VEL_RESISTENCE 50
#define MAX_SPEED 350
#define ROTATE_SPEED M_PI*1.5
#define BASE_NUMBER_ASTEROID 6
#define DISPAY_READY_MSG 3
#define BULLET_SPEED 500
#define BULLET_WIDTH 2
#define BULLET_HEIGHT 2
#define BULLET_DISTANCE 400
#define MAX_ASTEROID_SPEED 100
#define MAX_ASTEROID_SIZE 30
#define MAX_ASTEROID_ROTATION 90
#define MIN_ASTEROID_ROTATION 45
#define ASTEROID_SPRITE_ROTATIONS 180
#define SKIN_PATH "files/ship.bmp"
#define EXPLOSION_PATH "files/explosion.bmp"
#define ASTEROID_PATH "files/asteroid.bmp"
#define PLAYER_WIDTH 17
#define PLAYER_HEIGHT 17
#define SPRITE_ROTATIONS 72
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32 


class Object{
protected:
    float xPos;
    float yPos;
    float xVel;
    float yVel;
    int height;
    int width;
public:
    static SDL_Surface * explosion;
    SDL_Rect getPosition();
    virtual ~Object() = 0;
    virtual void drawObject(SDL_Surface *dst) = 0;
    virtual void moveObject(uint32_t delta) = 0;
};

class Bullet : public Object{
private:
    float distance;
public:
    Bullet(float direction, float x, float y);
    ~Bullet();
    void drawObject(SDL_Surface * dst);
    void moveObject(uint32_t delta);
    float getDistance();
};

class Asteroid : public Object{
private:
    uint8_t size;
    float direction;
    int rotation;
    int pointValue;
public:
    static SDL_Surface** rotatedSprites;
    Asteroid(uint8_t inSize, int x = SCREEN_WIDTH, int y = SCREEN_HEIGHT, int xOffset = 0, int yOffset = 0);
    ~Asteroid();
    void drawObject(SDL_Surface * dst);
    void moveObject(uint32_t delta);
    Asteroid** split();
    void bounce();
    int getPoints();
};

class Player : public Object{
private:
    Bullet** bullets;
    uint32_t score;
    int8_t rotation;
    uint8_t lives;
    float speed;
    float direction;
    float timer;
	bool accelerate;
    bool invincibility;
    bool exploding;
public:
    static SDL_Surface** rotatedSprites;
    Player();
    ~Player();
    void drawObject(SDL_Surface * dst);
    void death();
    void moveObject(uint32_t delta);
    void fire();
    void deleteBulletAt(uint8_t i);
    void increaseScore(int amount);
    int reload();
    bool isAccelerating();
    bool isInvincible();
    bool bulletExistsAt(uint8_t i);
    void setAccelerate(bool acc);
    void reset();
    void setRotation(int dir);
    int getLives();
    int getRotation();
    int getScore();
    SDL_Rect getBulletPosition(uint8_t i);
};

#endif	/* PLAYER_H */

