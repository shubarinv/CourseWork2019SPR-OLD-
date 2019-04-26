//
// Created by vhundef on 18.04.19.
//

#ifndef COURSEWORK_PARTICLE_H
#define COURSEWORK_PARTICLE_H


#include <SDL/SDL_video.h>
#include "game_object.h"

class particle :gameObject{
public:
	particle();
	void updateParticle();
	void initl(SDL_Surface *scrn, int max_X, int max_Y, bool b);
	coords getLocation();
	void setLoc(int x);
	void setLoc(int x,int y);

private:
	SDL_Rect particleBody;
	int max_x, max_y;
	SDL_Surface* screen;

	void drawParticle();

	void moveParticle();

	bool isOnScreen=true;

	bool isOwnedByPl;
public:
	void setIsOnScreen(bool isOnScreen);

public:
	bool getIsOnScreen() const;

};


#endif //COURSEWORK_PARTICLE_H
