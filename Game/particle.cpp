//
// Created by vhundef on 18.04.19.
//

#include <SDL/SDL_draw.h>
#include <iostream>
#include "particle.h"

particle::particle() {

}

void particle::initl(SDL_Surface *scrn, int max_X, int max_Y) {
	particleBody.x = max_X / 2-1;
	particleBody.y = max_Y-50;
	particleBody.h = 9;
	particleBody.w = 4;
	max_x = max_X;
	max_y = max_Y;
	screen = scrn;
}

void particle::drawParticle() {

	SDL_FillRect(screen, &particleBody, 0xFF0000);
}

void particle::moveParticle() {
	if (particleBody.y >= 4)
		particleBody.y -= 3;
	else
		isOnScreen = false;

}

void particle::updateParticle() {
	if (isOnScreen)
		if (particleBody.y > 0) {
			moveParticle();
			drawParticle();
		}
}

gameObject::coords particle::getLocation() {
	if (isOnScreen) {
		location.x1 = particleBody.x;
		location.y1 = particleBody.y;
		location.x2 = particleBody.x + particleBody.h;
		location.y2 = particleBody.y + particleBody.w;
	} else
		location = {100000, 100000, 100000, 10000};
	return location;
}

bool particle::getIsOnScreen() const {
	return isOnScreen;
}

void particle::setIsOnScreen(bool bIsOnScreen) {
	particle::isOnScreen = bIsOnScreen;
}

void particle::setLoc(int i) {
	particleBody.x=i;
}

