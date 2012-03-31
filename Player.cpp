#include "Objects.h"

SDL_Surface** Player::rotatedSprites;

Player::Player(){
    bullets = new Bullet*[MAX_BULLETS];
    for(int i = 0; i < MAX_BULLETS; i++){
        bullets[i] = NULL;
    }
    xPos = (SCREEN_WIDTH - width) / 2;
    yPos = (SCREEN_HEIGHT - height) / 2;
    speed = 0;
    xVel = 0;
    yVel = 0;
    rotation = 0;
    direction = M_PI / 2;
    score = 0;
    rotation = 0;
    accelerate = false;
    invincibility = false;
    exploding = false;
    timer = 0;
    height = PLAYER_HEIGHT;
    width = PLAYER_WIDTH;
    lives = 3;
}

Player::~Player(){
    for(int i = 0; i < MAX_BULLETS; i++){
        delete bullets[i];
    }
    delete [] bullets;
}

bool Player::isAccelerating(){
    return accelerate;
}

void Player::setAccelerate(bool acc){
    accelerate = acc;
}

void Player::setRotation(int dir){
    rotation += dir;
}

bool Player::bulletExistsAt(uint8_t i){
    if(bullets[i] == NULL)
        return false;
    else
        return true;
}

SDL_Rect Player::getBulletPosition(uint8_t i){
        return bullets[i]->getPosition();
}

int Player::reload(){
    for(int i = 0; i < MAX_BULLETS; i++){
        if(bullets[i] == NULL)
            return i;
    }
    return -1;
}

void Player::fire() {
    if (!exploding) {
        float xSpawn = xPos + width / 2 + (width / 2 * cos(direction));
        float ySpawn = yPos + height / 2 - (height / 2 * sin(direction));

        int i = reload();
        if (i != -1) {
            bullets[i] = new Bullet(direction, xSpawn, ySpawn);
        }
    }
}

void Player::deleteBulletAt(uint8_t i){
    delete bullets[i];
    bullets[i] = NULL;
}

void Player::moveObject(uint32_t delta) {
    if (!exploding) {
        //acceleration
        if (isAccelerating()) {
            xVel += cos(direction) * ACC_RATE * delta / 1000.f;
            yVel += sin(direction) * ACC_RATE * delta / 1000.f;
        }

        //apply resistence
        //not happy with this part, cluttered and can make the player "bounce" when almost still
        if (xVel > 0)
            xVel -= VEL_RESISTENCE * delta / 1000.f;
        else
            xVel += VEL_RESISTENCE * delta / 1000.f;
        if (yVel > 0)
            yVel -= VEL_RESISTENCE * delta / 1000.f;
        else
            yVel += VEL_RESISTENCE * delta / 1000.f;

        //speed cap
        if (xVel > MAX_SPEED)
            xVel = MAX_SPEED;
        else if (xVel < -MAX_SPEED)
            xVel = -MAX_SPEED;
        if (yVel > MAX_SPEED)
            yVel = MAX_SPEED;
        else if (yVel < -MAX_SPEED)
            yVel = -MAX_SPEED;


        //rotation
        direction = fmod((direction + (rotation * ROTATE_SPEED * delta / 1000.f)), M_PI * 2);
        if (direction < 0)
            direction += M_PI * 2;

        //movement
        xPos += xVel * (delta / 1000.f);
        if (xPos > SCREEN_WIDTH)
            xPos = 0 - width;
        else if (xPos < (0 - width))
            xPos = SCREEN_WIDTH;
        yPos -= yVel * (delta / 1000.f);
        if (yPos > SCREEN_HEIGHT)
            yPos = 0 - height;
        else if (yPos < 0 - height)
            yPos = SCREEN_HEIGHT;

        if (invincibility) {
            timer += delta / 1000.f;
            if (timer > INVIS_TIME) {
                invincibility = false;
                timer = 0;
            }
        }
    } else if (exploding) {
        timer += delta / 1000.f;
        if (timer > EXPLO_TIME && lives != 0) {
            exploding = false;
            timer = 0;
            reset();
        }
    }
    //bullet movement here too
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i] != NULL) {
            bullets[i]->moveObject(delta);
            if (bullets[i]->getDistance() > BULLET_DISTANCE) {
                deleteBulletAt(i);
            }
        }
    }
}


void Player::drawObject(SDL_Surface* dst){
    if(!(invincibility && (fmod(timer, 0.3) > 0.15)) && !exploding){
        //convert to radians to degrees
        double rotAngleDegree = ((direction - M_PI/2) * 180/M_PI);
         //kill offset
        if(rotAngleDegree < 0){
                rotAngleDegree += 360;
        }
        int i = (int) (rotAngleDegree / (360 / SPRITE_ROTATIONS));
        applySurface(rotatedSprites[i], dst,
                         (int) (xPos - rotatedSprites[i]->w/2 + rotatedSprites[0]->w/2), 
                         (int) (yPos - rotatedSprites[i]->h/2 + rotatedSprites[0]->h/2));
    }
    else if(exploding)
        applySurface(explosion, dst, (int) xPos, (int) yPos);
    
    //draw bullets
    for(int i = 0; i < MAX_BULLETS; i++){
                if(bullets[i] != NULL)
                        bullets[i]->drawObject(dst);
    }   
}

void Player::reset(){
    xPos = (SCREEN_WIDTH - width) / 2;
    yPos = (SCREEN_HEIGHT - height) / 2;
    speed = 0;
    xVel = 0;
    yVel = 0;
    direction = M_PI / 2;
    accelerate = false;
    for(int i = 0; i<MAX_BULLETS;i++){
        if(bullets[i] != NULL)
        delete bullets[i];
        bullets[i] = NULL;
    }
}

void Player::death(){
    lives--;
    exploding = true;
    invincibility = true;
    timer = 0;
}

bool Player::isInvincible(){
    return invincibility;
}

int Player::getScore(){
    return score;
}

void Player::increaseScore(int amount){
    score += amount;
}

int Player::getLives(){
    return lives;
}
