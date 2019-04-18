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
	SDL_Rect r, r_new, tower, flag,* shipParts[3]{&r, &tower, &flag};

	TBD movementSpeed;
	int movementDirrection, health, price,max_x=1280,max_y=720;
public:
	int getHealth() const;

	void setHealth(int health);

	int getPrice() const;

	void setPrice(int price);

private:
	char type;

	void shipCheck();

public:
	void reDraw(SDL_Surface*);
	Ship();
	TBD getAllCoords();
};


#endif //COURCEWORK_SHIP_H
