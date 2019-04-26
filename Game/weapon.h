//
// Created by vhundef on 17.04.19.
//

#ifndef COURSEWORK_WEAPON_H
#define COURSEWORK_WEAPON_H


#include "particle.h"

class Weapon:gameObject {
private:
	particle *particles;
	int totalParticlesOnScreen = 0;
	SDL_Surface *screen;
	int max_x, max_y,hitLoc=-999;
	bool bOwnedByPlayer;
public:
	int getHitLoc() const;

private:
	SDL_Rect rb;
public:
	void shoot(int);
	void shoot(int,int);

	void updateParticles();

	void reset(int wave) {
		delete(particles);
		totalParticlesOnScreen=0;
		particles = new particle[wave * 32 + 20];
		for (int i = 0; i < wave * 32 + 20; ++i) {
			particles[i].initl(screen, max_x, max_y, bOwnedByPlayer);
		}
	}

	int checkCollisions(coords);
	Weapon(SDL_Surface *scrn, int max_x, int max_y,bool);
};


#endif //COURSEWORK_WEAPON_H
