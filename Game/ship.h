//
// Created by vhundef on 17.04.19.
//

#ifndef COURCEWORK_SHIP_H
#define COURCEWORK_SHIP_H

#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include "game_object.h"
#include "weapon.h"


class Ship:gameObject{
private:
	SDL_Rect r, r_new, tower, flag,* shipParts[3]{&r, &tower, &flag};
	bool bAllowedToShoot;
public:
	bool isBAllowedToShoot() const;

	void setBAllowedToShoot(bool bAllowedToShoot);

private:
	int movementSpeed, maxSpeed;
public:
	int getMaxSpeed() const;

public:
	void setMovementSpeed(int movementSpeed);

private:
	int movementDirrection, health,max_x=1280,max_y=720, *hitLoc,hitsTaken=0;
	int propSpeedLoc=0;
	SDL_Surface *screen;

public:
	void setWeapon(const Weapon &weapon);
	Weapon weapon=Weapon(screen,1280,720, false);
	void setScreen(SDL_Surface *screen);

	int getHealth() const;

	void setHealth(int health);


	void spawnHit(int);


public:
	void reDraw(coords);
	Ship();
	coords getCoords();

	void moveShip(SDL_Rect **shipParts, int leftright, int speed);
};


#endif //COURCEWORK_SHIP_H
