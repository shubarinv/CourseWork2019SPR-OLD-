//
// Created by vhundef on 17.04.19.
//

#include <iostream>
#include <SDL/SDL_draw.h>
#include "weapon.h"

using namespace std;


void Weapon::shoot(int x) {
	totalParticlesOnScreen++;
	particles[totalParticlesOnScreen - 1].setLoc(x);
//	Draw_Line(screen, max_x / 2, max_y - 10, max_x / 2, 50, 0x00);
}

Weapon::Weapon(SDL_Surface *scrn, int max_X, int max_Y, bool bIsOwnedByPl) {
	screen = scrn;
	max_x = max_X;
	max_y = max_Y;
	rb.w = 4;
	rb.h = 8;
	totalParticlesOnScreen = 0;
	bOwnedByPlayer = bIsOwnedByPl;
	particles = new particle[2];
	for (int i = 0; i < 2; ++i) {
		particles[i].initl(screen, max_x, max_y, bOwnedByPlayer);
	}
}

void Weapon::updateParticles() {
	for (int i = 0; i < totalParticlesOnScreen; ++i) {
		particles[i].updateParticle();
	}
}

int Weapon::checkCollisions(gameObject::coords ship) {
	int totalHits = 0;
	for (int i = 0; i < totalParticlesOnScreen; ++i) {
		if (!particles[i].getIsOnScreen())
			continue;
		else {
			if (particles[i].getLocation().x1 == 100000)
				continue;
			if (ship.x1 - particles[i].getLocation().x1 <= 0 && ship.x2 - particles[i].getLocation().x2 >= 0) {
				if (bOwnedByPlayer) {
					if (ship.y1 - particles[i].getLocation().y1 <= 0 && ship.y2 - particles[i].getLocation().y2 >= 0) {
						totalHits++;
						hitLoc = (particles[i].getLocation().x1 + particles[i].getLocation().x2) / 2;
						particles[i].setIsOnScreen(false);
					}
				} else {
					if (ship.y1 - particles[i].getLocation().y1 <= 0 && ship.y2 - particles[i].getLocation().y2 >= 0) {
						cout<<"Player ship Y: "<<ship.y1<<endl;
						cout<<"Particle Y: "<<particles[i].getLocation().y1<<endl;
						totalHits++;
						hitLoc = (particles[i].getLocation().x1 + particles[i].getLocation().x2) / 2;
						particles[i].setIsOnScreen(false);
					}
				}
			}

		}
	}
	return totalHits;
}

int Weapon::getHitLoc() const {
	return hitLoc;
}

void Weapon::shoot(int x, int y) {
	totalParticlesOnScreen++;
	particles[totalParticlesOnScreen - 1].setLoc(x, y);
}
