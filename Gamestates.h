/*
 * Gamestates.h
 *
 *  Created on: Jan 19, 2012
 *      Author: msegersten
 */

#ifndef GAMESTATES_H_
#define GAMESTATES_H_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <string>
#include "Objects.h"
#include "timer.h"
#include <vector>
#include <cstdlib>
#include <sstream>

#define FONT_PATH "files/8bit.ttf"
#define FONT_SIZE 14
#define NUMBER_OF_MENU_ITEMS 4
#define NUMBER_OF_INTRO_MESSAGES 2
#define NUMBER_OF_HUD_MESSAGES 5
#define NUMBER_OF_CREDITS 7
#define DISPLAY_READY_MSG 3
#define DISPLAY_LVL_COMPLETE 4
#define DISPLAY_GAME_OVER 6

enum STATES {
    GAMESTATE_GAMEPLAY,
    GAMESTATE_INTRO,
    GAMESTATE_CREDITS,
    GAMESTATE_EXIT,
    GAMESTATE_MENU,
};

class Gamestate {
protected:
    u_int8_t id;
    u_int8_t next_state;
    u_int32_t time;
    SDL_Surface** messages;
    int* message_width;

public:
    static TTF_Font *gamefont;
    static SDL_Color font_color;
    virtual ~Gamestate();
    void setNextState(u_int8_t i);
    int nextState();
    int currentState();
    virtual void handleInput(SDL_Event &event) = 0;
    virtual void update(u_int32_t delta_timer) = 0;
    virtual void render(SDL_Surface * screen) = 0;
};

class Gamestate_Intro : public Gamestate {
public:
    Gamestate_Intro();
    ~Gamestate_Intro();
    void handleInput(SDL_Event &event);
    void update(u_int32_t delta_timer);
    void render(SDL_Surface * screen);
};

class Gamestate_Menu : public Gamestate {
private:
    u_int8_t select;
public:
    Gamestate_Menu();
    ~Gamestate_Menu();
    void handleInput(SDL_Event &event);
    void update(u_int32_t delta_timer);
    void render(SDL_Surface * screen);

};

class Gamestate_Gameplay : public Gamestate{
private:
    Player* player1;
    Timer delta_timer;
    std::vector<Asteroid*> asteroids;
    std::stringstream dataToString;
    int level;
    int asteroidsLeft;
    bool displayReady;
    bool gameOver;
public:
    Gamestate_Gameplay();
    ~Gamestate_Gameplay();
    void handleInput(SDL_Event &event);
    void update(u_int32_t delta_timer);
    void render(SDL_Surface * screen);
    void initiateLevel();
    void renderHUD(SDL_Surface * screen);
};

class Gamestate_Exit : public Gamestate{
public:
    Gamestate_Exit();
    ~Gamestate_Exit();
    void handleInput(SDL_Event &event);
    void update(u_int32_t delta_timer);
    void render(SDL_Surface * screen);
};


class Gamestate_Credits : public Gamestate{
public:
    Gamestate_Credits();
    ~Gamestate_Credits();
    void handleInput(SDL_Event &event);
    void update(u_int32_t delta_timer);
    void render(SDL_Surface * screen);
};

#endif /* GAMESTATES_H_ */
