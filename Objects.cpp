#include "Objects.h"

SDL_Surface* Object::explosion;
SDL_Surface** Asteroid::rotatedSprites;

Object::~Object(){}

SDL_Rect Object::getPosition(){
    SDL_Rect position;
    position.x = (int) xPos;
    position.y = (int) yPos;
    position.h = height;
    position.w = width;
    return position;
}

Bullet::Bullet(float direction, float x, float y){
    xVel = BULLET_SPEED * cos(direction);
    yVel = BULLET_SPEED * sin(direction);
    height = BULLET_HEIGHT;
    width = BULLET_WIDTH;
    xPos = x;
    yPos = y;   
    distance = 0;
}

Bullet::~Bullet(){}

void Bullet::moveObject(uint32_t delta){
    xPos += xVel * (delta / 1000.f);
    if(xPos > SCREEN_WIDTH)
        xPos = 0 - width;
    else if(xPos < (0 - width))
        xPos = SCREEN_WIDTH;
    
    yPos -= yVel * (delta / 1000.f);
    if(yPos > SCREEN_HEIGHT)
        yPos = 0 - height;
    else if(yPos < (0 - height))
        yPos = SCREEN_HEIGHT;
    
    distance += sqrt((xVel * (delta / 1000.f)) * (xVel * (delta / 1000.f)) + 
                (yVel * (delta / 1000.f)) * (yVel * delta / 1000.f));
}

void Bullet::drawObject(SDL_Surface* dst){
    SDL_Rect temp;
    temp.x = (int) xPos;
    temp.y = (int) yPos;
    temp.w = width;
    temp.h = height;
    SDL_FillRect(dst, &temp, SDL_MapRGB(dst->format, 0xFF, 0xFF, 0xFF));
}

float Bullet::getDistance(){
    return distance;
}

Asteroid::Asteroid(uint8_t inSize, int x, int y, int xOffset, int yOffset){ 
    xPos = xOffset + rand()%(x/2+1);
    if(xPos > x/4)
        xPos += x/2;
        
    yPos = yOffset + rand()%(y/2+1);
    if(yPos > y/4)
        yPos += y/2;
        
    xVel = rand()%MAX_ASTEROID_SPEED*2+1;
    if(xVel > MAX_ASTEROID_SPEED)
        xVel -= MAX_ASTEROID_SPEED*2;
        
    yVel = rand()%MAX_ASTEROID_SPEED*2+1;
    if(yVel > MAX_ASTEROID_SPEED)
        yVel -= MAX_ASTEROID_SPEED*2;
    
    rotation = MIN_ASTEROID_ROTATION + rand()%MAX_ASTEROID_ROTATION+1; 
    
    pointValue = 300 / inSize;
    size = inSize;
    direction = 0;
    height = MAX_ASTEROID_SIZE * inSize;
    width = MAX_ASTEROID_SIZE * inSize;
}

Asteroid::~Asteroid(){}

void Asteroid::moveObject(uint32_t delta){
    xPos += xVel * (delta / 1000.f);
    if(xPos > SCREEN_WIDTH)
        xPos = 0 - width;
    else if(xPos < (0 - width))
        xPos = SCREEN_WIDTH;
    yPos -= yVel * (delta / 1000.f);
    if(yPos > SCREEN_HEIGHT)
        yPos = 0 - height;
    else if(yPos < (0 - height))
        yPos = SCREEN_HEIGHT;
    
    //only acts as an index to show frame
    direction = fmod((direction + delta / 1000.f * rotation), 360);
}

void Asteroid::drawObject(SDL_Surface* dst){
    SDL_Rect temp;
    temp.x = (int) xPos;
    temp.y = (int) yPos;
    temp.w = width;
    temp.h = height;
    //SDL_FillRect(dst, &temp, SDL_MapRGB(dst->format, 0xFF, 0x00, 0x00));
    
    int i = (int) (direction / (360 / ASTEROID_SPRITE_ROTATIONS)) + ((size-1) * ASTEROID_SPRITE_ROTATIONS);
    applySurface(rotatedSprites[i], dst,
                         (int) (xPos - rotatedSprites[i]->w/2 + rotatedSprites[(size-1)*ASTEROID_SPRITE_ROTATIONS]->w/2), 
                         (int) (yPos - rotatedSprites[i]->h/2 + rotatedSprites[(size-1)*ASTEROID_SPRITE_ROTATIONS]->h/2));

}   

void Asteroid::bounce(){}

Asteroid** Asteroid::split(){
    Asteroid** array = NULL;
    if(size > 1){
        array = new Asteroid*[2];
        array[0] = new Asteroid(size - 1, width, height, xPos, yPos);
        array[1] = new Asteroid(size - 1, width, height, xPos, yPos);
    }
        return array;
}

int Asteroid::getPoints(){
    return pointValue;
}