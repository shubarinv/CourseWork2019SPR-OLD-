//
// Created by vhundef on 17.04.19.
//

#include <iostream>
#include <SDL/SDL_draw.h>
#include "weapon.h"

using namespace std;


void Weapon::shoot() {
	cout << "Шпидяу" << endl;
	totalParticlesOnScreen++;
	Draw_Line(screen, max_x / 2, max_y - 10, max_x / 2, 50, 0x00);
}

Weapon::Weapon(SDL_Surface *scrn, int max_X, int max_Y) {
	screen = scrn;
	max_x = max_X;
	max_y = max_Y;
	rb.w = 4;
	rb.h = 8;
	totalParticlesOnScreen = 0;
	particles = new particle[8];
	for (int i = 0; i < 8; ++i) {
		particles[i].initl(screen, max_x, max_y);
	}
}

void Weapon::updateParticles() {
	for (int i = 0; i < totalParticlesOnScreen; ++i) {
		particles[i].updateParticle();
	}
}