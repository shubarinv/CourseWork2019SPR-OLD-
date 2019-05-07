//
// Created by vhundef on 23.04.19.
//

#ifndef COURSEWORK_PLAYER_SHIP_H
#define COURSEWORK_PLAYER_SHIP_H


#include <SDL/SDL_video.h>
#include "game_object.h"

class PlayerShip : gameObject{
private:
	SDL_Rect r, r_new, tower, flag,* shipParts[3]{&r, &tower,&flag};

	int movementSpeed,maxMovementSpeed,maxHealth;
public:
	int getMaxHealth() const;

	void setMaxHealth(int maxHealth);

public:
	int getMaxMovementSpeed() const;

	void setMaxMovementSpeed(int maxMovementSpeed);

private:
	int movementDirection, health,max_x=1280,max_y=720, *hitLoc,hitsTaken=0;
public:
	int getMovementDirection() const;

public:
	void setMovementSpeed(int movementSpeed);

	void setMovementDirection(int movementDirection);

private:
	void moveShip();
	void drawShip(SDL_Surface *);

public:
	int getHealth() const;

	void setHealth(int health);

	void spawnHit(int);

public:
	void reDraw(SDL_Surface*);
	PlayerShip();
	coords getCoords();
};



#endif //COURSEWORK_PLAYER_SHIP_H
