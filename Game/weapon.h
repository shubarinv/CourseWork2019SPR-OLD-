//
// Created by vhundef on 17.04.19.
//

#ifndef COURSEWORK_WEAPON_H
#define COURSEWORK_WEAPON_H


#include "particle.h"

class Weapon {
private:
	particle *particles;
	int totalParticlesOnScreen = 0;
	SDL_Surface *screen;
	int max_x, max_y;
	SDL_Rect rb;
public:
	void shoot();

	void updateParticles();

	void reset(int wave) {
		particles = new particle[wave * 6 + 10];
		for (int i = 0; i < wave * 6 + 10; ++i) {
			particles[i].initl(screen, max_x, max_y);
		}
	}

	Weapon(SDL_Surface *scrn, int max_x, int max_y);
};


#endif //COURSEWORK_WEAPON_H
