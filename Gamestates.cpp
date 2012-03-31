/*
 * Gamestates.cpp
 *
 *  Created on: Jan 19, 2012
 *      Author: msegersten
 */

#include "Gamestates.h"
using namespace std;

SDL_Color Gamestate::font_color = {255, 255, 255};
TTF_Font* Gamestate::gamefont;

int Gamestate::currentState() {
    return id;
}

void Gamestate::setNextState(u_int8_t i) {
    next_state = i;
}

int Gamestate::nextState() {
    return next_state;
}

Gamestate::~Gamestate() {}

Gamestate_Intro::Gamestate_Intro() {
    id = GAMESTATE_INTRO;
    next_state = id;
    time = 0;
    
    messages = new SDL_Surface*[NUMBER_OF_INTRO_MESSAGES];
    messages[0] = TTF_RenderText_Solid(gamefont, "space war ", font_color);
    messages[1] = TTF_RenderText_Solid(gamefont, "press any key", font_color);
    
    message_width = new int[NUMBER_OF_INTRO_MESSAGES];
    TTF_SizeText(gamefont, "space war", &message_width[0], NULL);
    TTF_SizeText(gamefont, "press any key", &message_width[1], NULL);
}

Gamestate_Intro::~Gamestate_Intro() {
    for(int i = 0; i < NUMBER_OF_INTRO_MESSAGES; i++){
        SDL_FreeSurface(messages[i]);
    }
    delete [] messages;
    delete [] message_width;
}

void Gamestate_Intro::handleInput(SDL_Event &event) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN)
            setNextState(GAMESTATE_MENU);
    }
}

void Gamestate_Intro::update(u_int32_t delta_timer){
    time += delta_timer;
    if(time > 2000)
        time = 0;
}

void Gamestate_Intro::render(SDL_Surface *screen) {
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    applySurface(messages[0], screen, (SCREEN_WIDTH - message_width[0]) / 2, 240);
    if(time < 1000)
        applySurface(messages[1], screen, (SCREEN_WIDTH - message_width[1]) / 2, 340);
}

Gamestate_Menu::Gamestate_Menu() {
    id = GAMESTATE_MENU;
    next_state = id;
    select = 0;
    time = 0;
    
    messages = new SDL_Surface*[NUMBER_OF_MENU_ITEMS];
    messages[0] = TTF_RenderText_Solid(gamefont, "New Game", font_color);
    messages[1] = TTF_RenderText_Solid(gamefont, "Intro", font_color);
    messages[2] = TTF_RenderText_Solid(gamefont, "Credits", font_color);
    messages[3] = TTF_RenderText_Solid(gamefont, "Exit", font_color);

    message_width = new int[NUMBER_OF_MENU_ITEMS];
    TTF_SizeText(gamefont, "New Game", &message_width[0], NULL);
    TTF_SizeText(gamefont, "Intro", &message_width[1], NULL);
    TTF_SizeText(gamefont, "Credits", &message_width[2], NULL);
    TTF_SizeText(gamefont, "Exit", &message_width[3], NULL);
}

Gamestate_Menu::~Gamestate_Menu() {
    for (int i = 0; i < NUMBER_OF_MENU_ITEMS; i++) {
        SDL_FreeSurface(messages[i]);
    }
    delete [] messages;
    delete [] message_width;
}

void Gamestate_Menu::handleInput(SDL_Event &event) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN)
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (select == 0)
                        select = 3;
                    else
                        select--;
                    break;
                case SDLK_DOWN:
                    if (select == 3)
                        select = 0;
                    else
                        select++;
                    break;
                case SDLK_RETURN:
                    setNextState(select);
                    break;
                case SDLK_ESCAPE:
                    setNextState(GAMESTATE_EXIT);
                    break;
                default:
                    break;
            }
    }
}

void Gamestate_Menu::update(u_int32_t delta_timer){
    time += delta_timer;
}

void Gamestate_Menu::render(SDL_Surface *screen) {
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    int middle_of_screen_x = SCREEN_WIDTH / 2;

    for (int i = 0; i < NUMBER_OF_MENU_ITEMS; i++) {
        applySurface(messages[i], screen,
                middle_of_screen_x - (message_width[i] / 2),
                262 + i * (FONT_SIZE+6));
    }
    SDL_Rect temp;
    temp.h = 2;
    temp.w = message_width[select];
    temp.x = middle_of_screen_x - (message_width[select] / 2);
    temp.y = 255 + (select+1) * (FONT_SIZE+6);
    
    SDL_FillRect(screen, &temp, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
}


Gamestate_Exit::Gamestate_Exit(){
    id = GAMESTATE_EXIT;
    next_state = id;
    time = 0;
    messages = new SDL_Surface*[1];
    messages[0] = TTF_RenderText_Solid(gamefont, "Thank you for playing!", font_color);
    message_width = new int[1];
    TTF_SizeText(gamefont, "Thank you for playing!", &message_width[0], NULL);
}
Gamestate_Exit::~Gamestate_Exit(){
    SDL_FreeSurface(messages[0]);
    delete [] messages;
    delete [] message_width;
}
void Gamestate_Exit::handleInput(SDL_Event &event){}
void Gamestate_Exit::update(u_int32_t delta_timer){}
void Gamestate_Exit::render(SDL_Surface * screen){
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    applySurface(messages[0], screen, (SCREEN_WIDTH - message_width[0]) / 2, SCREEN_HEIGHT / 2 - 100);
}

Gamestate_Credits::Gamestate_Credits(){
    id = GAMESTATE_CREDITS;
    next_state = id;
    time = 0;
    messages = new SDL_Surface*[NUMBER_OF_CREDITS];
    messages[0] = TTF_RenderText_Solid(gamefont, "Code and 'artwork' by Martin Segersten", font_color);
    messages[1] = TTF_RenderText_Solid(gamefont, "Special thanks to", font_color);
    messages[2] = TTF_RenderText_Solid(gamefont, "Lazy Foo' Productions for his great tutorials found at lazyfoo.net", font_color);
    messages[3] = TTF_RenderText_Solid(gamefont, "My roommates for withstanding me using the microwave at 4 in the morning", font_color);
    messages[4] = TTF_RenderText_Solid(gamefont, "My best friend, girlfriend and love of my life, Darrah. I love you.", font_color);
    messages[5] = TTF_RenderText_Solid(gamefont, "The Detroit Red Wings for keeping me company at night", font_color);
    messages[6] = TTF_RenderText_Solid(gamefont, "... and to YOU for playing this game!", font_color);
}
Gamestate_Credits::~Gamestate_Credits(){
    for(int i = 0; i < NUMBER_OF_CREDITS; i++){
        SDL_FreeSurface(messages[i]);
    }
    delete [] messages;
}
void Gamestate_Credits::handleInput(SDL_Event &event){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN)
            setNextState(GAMESTATE_MENU);
    }
}

void Gamestate_Credits::update(u_int32_t delta_timer){
    time += delta_timer;
    if(time /30 > SCREEN_HEIGHT + SCREEN_HEIGHT / 4){
        time = 0;
    }
}

void Gamestate_Credits::render(SDL_Surface * screen){
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    applySurface(messages[0], screen, 20, SCREEN_HEIGHT - 50 - time/30);
    for(int i = 1; i < NUMBER_OF_CREDITS; i++){
        applySurface(messages[i], screen, 20, SCREEN_HEIGHT + i*2*FONT_SIZE - time/30 - 50);
    }
}