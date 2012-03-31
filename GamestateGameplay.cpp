#include "Gamestates.h"

Gamestate_Gameplay::Gamestate_Gameplay(){
    id = GAMESTATE_GAMEPLAY;
    next_state = id;
    messages = new SDL_Surface*[NUMBER_OF_HUD_MESSAGES];
    message_width = new int[NUMBER_OF_HUD_MESSAGES];
    messages[0] = TTF_RenderText_Solid(gamefont, "Get ready!", font_color);
    messages[1] = NULL;
    messages[2] = TTF_RenderText_Solid(gamefont, "Level complete!", font_color);
    messages[3] = NULL;
    messages[4] = TTF_RenderText_Solid(gamefont, "GAME OVER", font_color);
    TTF_SizeText(gamefont, "Get ready!", &message_width[0], NULL);
    TTF_SizeText(gamefont, "Level complete!", &message_width[2], NULL);
    TTF_SizeText(gamefont, "Game over!", &message_width[4], NULL);
    level = 0;
    gameOver = false;
    player1 = new Player();
    srand(SDL_GetTicks());
    initiateLevel();
}

Gamestate_Gameplay::~Gamestate_Gameplay(){
    delete player1;    
   
    //free memory used by asteroid objects
    for(std::vector<Asteroid*>::iterator it = asteroids.begin(); it!= asteroids.end(); ++it){
        if(*it != NULL){
            delete (*it);
        }
    }
    asteroids.clear();
    
	//free memory used by text and messages
    for(int i = 0; i < NUMBER_OF_HUD_MESSAGES; i++){
        if(messages[i] != NULL){
            SDL_FreeSurface(messages[i]);
            messages[i] = NULL;
        }
    }
    delete [] messages;
    delete [] message_width;
}

void Gamestate_Gameplay::handleInput(SDL_Event &event) {
    if (!displayReady) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        player1->setAccelerate(true);
                        break;
                    case SDLK_LEFT:
                        player1->setRotation(LEFT);
                        break;
                    case SDLK_RIGHT:
                        player1->setRotation(RIGHT);
                        break;
                    case SDLK_SPACE:
                        player1->fire();
                        break;
                    case SDLK_ESCAPE:
                        setNextState(GAMESTATE_MENU);
                    default:
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        player1->setAccelerate(false);
                        break;
                    case SDLK_LEFT:
                        player1->setRotation(-LEFT);
                        break;
                    case SDLK_RIGHT:
                        player1->setRotation(-RIGHT);
                        break;
                    default:
                        break;
                }

            }

        }
    }
}

void Gamestate_Gameplay::update(u_int32_t delta_timer) {
    if (!displayReady) {
        //movement, bullet movement inside player class
        player1->moveObject(delta_timer);
        for (std::vector<Asteroid*>::iterator it = asteroids.begin(); it != asteroids.end(); ++it) {
            if (*it != NULL) {
                (*it)->moveObject(delta_timer);
            }
        }

        for (int j = 0; j < asteroids.size(); j++) {
            if (asteroids.at(j) != NULL) {
                if (isColliding(player1->getPosition(), asteroids.at(j)->getPosition())) {
                    if (!player1->isInvincible()) {
                        player1->death();
                        time = 0;
                    }
                    break;
                }
            }
        }

        //collision detection bullets/asteroids
        SDL_Rect pos;
        Asteroid** temp = NULL;
        //for each bullet
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (player1->bulletExistsAt(i)) {
                pos = player1->getBulletPosition(i);
                
                //check against each asteroid
                for (int j = 0; j < asteroids.size(); j++) {
                    if (asteroids.at(j) != NULL) {
                        
                        //detect collision and perform actions
                        if (isColliding(pos, asteroids.at(j)->getPosition())) {
                            player1->deleteBulletAt(i);
                            player1->increaseScore(asteroids.at(j)->getPoints());
                            temp = asteroids.at(j)->split();
                            delete asteroids.at(j);
                            asteroids.at(j) = NULL;
                            if (temp != NULL) {
                                asteroids.at(j) = temp[0];
                                asteroids.push_back(temp[1]);
                                asteroidsLeft++;
                            } else
                                asteroidsLeft--;
                        }
                    }
                }
            }
        }
        if(player1->getLives() == 0){
            gameOver = true;
            if(time >= DISPLAY_GAME_OVER * 1000)
                setNextState(GAMESTATE_MENU);
            else
                time+= delta_timer;
        }
        else if (asteroidsLeft == 0) {
            time += delta_timer;
            if (time >= DISPLAY_LVL_COMPLETE * 1000) {
                initiateLevel();
                time = 0;
            }
        }

    } 
    else {
        time += delta_timer;
        if (time >= DISPLAY_READY_MSG * 1000) {
            displayReady = false;
            time = 0;
        }
    }
}
    
void Gamestate_Gameplay::render(SDL_Surface* screen){
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    
    player1->drawObject(screen);
    for(std::vector<Asteroid*>::iterator it = asteroids.begin(); it!= asteroids.end(); ++it){
        if(*it != NULL)
                (*it)->drawObject(screen);
    }
    renderHUD(screen);
}

void Gamestate_Gameplay::initiateLevel(){
    level++;
    player1->reset();
    
    //set messages
    if(messages[1] != NULL){
        SDL_FreeSurface(messages[1]);
        messages[1] = NULL;
    }
    dataToString.str(std::string());
    dataToString << "Level " << level;
    messages[1] = TTF_RenderText_Solid(gamefont, dataToString.str().c_str(), font_color);
    TTF_SizeText(gamefont, dataToString.str().c_str(), &message_width[1], NULL);
    
    
    asteroidsLeft = (BASE_NUMBER_ASTEROID + level * 2);
    asteroids.reserve((BASE_NUMBER_ASTEROID + level * 2) * 3);
    
    for(int i = 0; i < BASE_NUMBER_ASTEROID + level * 2; i++){
        asteroids.push_back(new Asteroid(3));
    }
    displayReady = true;
    time = 0;
}

void Gamestate_Gameplay::renderHUD(SDL_Surface * screen){
    
    dataToString.str(std::string());
    dataToString << "Score  " << player1->getScore();
    if(messages[3]!= NULL){
        SDL_FreeSurface(messages[3]);
        messages[3] = NULL;
    }
    messages[3] = TTF_RenderText_Solid(gamefont, dataToString.str().c_str(), font_color);
    TTF_SizeText(gamefont, dataToString.str().c_str(), &message_width[3], NULL);
    applySurface(messages[3], screen, 20, 20);
    
    if(displayReady){
        applySurface(messages[0], screen, (SCREEN_WIDTH - message_width[0]) / 2, SCREEN_HEIGHT / 2 - 100);
        applySurface(messages[1], screen, (SCREEN_WIDTH - message_width[1]) / 2, SCREEN_HEIGHT / 2 - 60);
    }
    else if(gameOver)
        applySurface(messages[4], screen, (SCREEN_WIDTH - message_width[4]) / 2, SCREEN_HEIGHT / 2 - 100);
    else if(asteroidsLeft == 0 && !gameOver)
        applySurface(messages[2], screen, (SCREEN_WIDTH - message_width[2]) / 2, SCREEN_HEIGHT / 2 - 100);

    for(int i = 0; i < player1->getLives()-1; i++)
        applySurface(Player::rotatedSprites[0], screen, SCREEN_WIDTH - 20*i - 40, 20);
    
}


