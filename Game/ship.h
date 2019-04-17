//
// Created by vhundef on 17.04.19.
//

#ifndef COURCEWORK_SHIP_H
#define COURCEWORK_SHIP_H

#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>

typedef int TBD;

class Ship {
private:
	SDL_Rect r, r_new, cleaner, tower, flag,* shipParts[3]{&r, &tower, &flag};

	TBD movementSpeed;
	int movementDirrection, health, price,max_x=1280,max_y=720;
	char type;

	void shipCheck();

public:
	void reDraw(SDL_Surface*);
	Ship();
	TBD getAllCoords();
};


#endif //COURCEWORK_SHIP_H
