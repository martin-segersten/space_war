/*
 * general.cpp
 *
 *  Created on: Jan 26, 2012
 *      Author: msegersten
 */

#include "general.h"
using namespace std;

SDL_Surface* loadImage(string fpath) {
    SDL_Surface* temp = NULL;
    SDL_Surface* optimizedImage = NULL;
    temp = SDL_LoadBMP(fpath.c_str());
    optimizedImage = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);
    return optimizedImage;
}

void applySurface(SDL_Surface *src, SDL_Surface *dst, int x, int y) {
    SDL_Rect temp;
    temp.x = x;
    temp.y = y;
    SDL_BlitSurface(src, NULL, dst, &temp);
}

bool isColliding(SDL_Rect boxone, SDL_Rect boxtwo){
	int boxoneTop = boxone.y;
	int boxoneBottom = boxone.y + boxone.h;
	int boxoneLeft = boxone.x;
	int boxoneRight = boxone.x + boxone.w;

	int boxtwoTop = boxtwo.y;
	int boxtwoBottom = boxtwo.y + boxtwo.h;
	int boxtwoLeft = boxtwo.x;
	int boxtwoRight = boxtwo.x + boxtwo.w;

	if(boxoneLeft >= boxtwoRight)
		return false;
	if(boxoneRight <= boxtwoLeft)
		return false;
	if(boxoneTop >= boxtwoBottom)
		return false;
	if(boxoneBottom <= boxtwoTop)
		return false;
	return true;

}


