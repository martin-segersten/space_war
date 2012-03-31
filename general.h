/*
 * general.h
 *
 *  Created on: Jan 26, 2012
 *      Author: msegersten
 */

#ifndef GENERAL_H_
#define GENERAL_H_
#include "SDL/SDL.h"
#include <string>

SDL_Surface* loadImage(std::string fpath);
void applySurface(SDL_Surface *src, SDL_Surface *dst, int x, int y);
bool isColliding(SDL_Rect obj1, SDL_Rect obj2);


#endif /* GENERAL_H_ */
