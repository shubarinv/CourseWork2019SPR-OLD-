//
// Created by vhundef on 18.04.19.
//

#include <SDL/SDL_draw.h>
#include "particle.h"

particle::particle() {

}

void particle::initl(SDL_Surface *scrn, int max_X, int max_Y) {
	particleBody.x = max_X / 2;
	particleBody.y = max_Y;
	particleBody.h = 4;
	particleBody.w = 4;
	max_x = max_X;
	max_y = max_Y;
	screen = scrn;
}

void particle::drawParticle() {
	Sint32 base_color = 0xFFB533; // Основной цвет (желтый)

	SDL_FillRect(screen, &particleBody, 0xFF0000);
}

void particle::moveParticle() {
	if (particleBody.y > 0)
		particleBody.y -= 3;

}

void particle::updateParticle() {
	if (particleBody.y > 0) {
		moveParticle();
		drawParticle();
	}
}
