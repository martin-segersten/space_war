/*
 * main.cpp
 *
 *  Created on: Jan 25, 2012
 *      Author: msegersten
 */

#include "Gamestates.h"
#include "general.h"
#include <stdio.h>
#include <iostream>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32


int init() {
    if (SDL_Init(SDL_INIT_EVERYTHING) == -1 || TTF_Init() == -1)
        return 0;
    else
        return 1;
}

int loadGFX() {
    //load gamefont
    Gamestate::gamefont = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    //load explosion
    Object::explosion = loadImage(EXPLOSION_PATH);

    //load asteroid & rotate sprites
    SDL_Surface* ref = loadImage(ASTEROID_PATH);
    Uint32 colorkey = SDL_MapRGB(ref->format, 0x00, 0x00, 0x00);
    Asteroid::rotatedSprites = new SDL_Surface*[ASTEROID_SPRITE_ROTATIONS * 3];
    for (int a = 0; a < 3; a++) {
        for (int i = 0; i < ASTEROID_SPRITE_ROTATIONS; i++) {
            int j = i + ASTEROID_SPRITE_ROTATIONS*a;
            Asteroid::rotatedSprites[j] = NULL;
            Asteroid::rotatedSprites[j] = rotozoomSurface(ref, (i * 360 / ASTEROID_SPRITE_ROTATIONS), 1 * (a + 1), 0);
            SDL_SetColorKey(Asteroid::rotatedSprites[j], SDL_SRCCOLORKEY, colorkey);
        }
    }
    SDL_FreeSurface(ref);
    ref = NULL;
    
    //load player & rotate sprites
    ref = loadImage(SKIN_PATH);
    Player::rotatedSprites = new SDL_Surface*[SPRITE_ROTATIONS];
    for(int i = 0; i < SPRITE_ROTATIONS; i++){
        Player::rotatedSprites[i] = NULL;
        Player::rotatedSprites[i] = rotozoomSurface(ref, (i * 360 / SPRITE_ROTATIONS), 1, 1);
        SDL_SetColorKey(Player::rotatedSprites[i], SDL_SRCCOLORKEY, colorkey);
    }
    SDL_FreeSurface(ref);
    ref = NULL;
    return 1;
}

int freeResources(){
    TTF_CloseFont(Gamestate::gamefont);
    SDL_FreeSurface(Object::explosion);
    for(int i = 0; i < ASTEROID_SPRITE_ROTATIONS * 3; i++)
        SDL_FreeSurface(Asteroid::rotatedSprites[i]);
    for(int i = 0; i < SPRITE_ROTATIONS; i++)
        SDL_FreeSurface(Player::rotatedSprites[i]);
    TTF_Quit();
    SDL_Quit();
    return 1;
}

Gamestate* changeState(Gamestate *current_state) {
    if (current_state->nextState() != current_state->currentState()) {
        int i = current_state->nextState();
        delete current_state;
        current_state = NULL;
        Gamestate * new_state = NULL;
        switch (i) {
            case GAMESTATE_GAMEPLAY:
                new_state = new Gamestate_Gameplay();
                break;
            case GAMESTATE_INTRO:
                new_state = new Gamestate_Intro();
                break;
            case GAMESTATE_CREDITS:
                new_state = new Gamestate_Credits();
                break;
            case GAMESTATE_EXIT:
                new_state = new Gamestate_Exit();
                break;
            case GAMESTATE_MENU:
                new_state = new Gamestate_Menu();
                break;
            default:
                break;
        }
        return new_state;
    }
    return current_state;
}


int main(int argc, char **argv) {
    init();
    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    loadGFX();
    Gamestate *currentGamestate = new Gamestate_Intro();
    SDL_Event event;
    Timer deltaTime = Timer();
    deltaTime.start();
    while (currentGamestate->currentState() != GAMESTATE_EXIT) {
        currentGamestate->handleInput(event);
        currentGamestate->update(deltaTime.get_ticks());
        deltaTime.start();
        currentGamestate = changeState(currentGamestate);
        currentGamestate->render(screen);                
        SDL_Flip(screen);
    }
    SDL_Delay(2000);
    delete currentGamestate;
    freeResources();
    SDL_FreeSurface(screen);
    return 0;
}



