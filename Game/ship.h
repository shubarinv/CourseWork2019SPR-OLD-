//
// Created by vhundef on 17.04.19.
//

#ifndef COURCEWORK_SHIP_H
#define COURCEWORK_SHIP_H

#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include "game_object.h"

typedef int TBD;

class Ship:gameObject{
private:
	SDL_Rect r, r_new, tower, flag,* shipParts[3]{&r, &tower, &flag};

	int movementSpeed;
	int movementDirrection, health, price,max_x=1280,max_y=720, *hitLoc,hitsTaken=0;
	int propSpeedLoc=0;

public:
	int getHealth() const;

	void setHealth(int health);

	int getPrice() const;

	void setPrice(int price);

	void spawnHit(int);

private:
	char type;

	void shipCheck();

public:
	void reDraw(SDL_Surface*);
	Ship();
	coords getCoords();

	void moveShip(SDL_Rect **shipParts, int leftright, int speed);
};


#endif //COURCEWORK_SHIP_H
