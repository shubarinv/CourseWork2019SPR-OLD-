//
// Created by vhundef on 17.04.19.
//


#include <iostream>
#include "hud.h"
using namespace std;

HUD::HUD(SDL_Surface *scrn) {
	if (TTF_Init()) {
		throw;
	}
	if (!(fnt = TTF_OpenFont("Roboto-Regular.ttf", 18))) {
		TTF_Quit();
		SDL_Quit();
		throw;
	}
	text_color.r = 0;
	text_color.g = 0;
	text_color.b = 0;

	text_rect.w = 1;
	text_rect.h = 1;

	screen=scrn;
}


void HUD::reDraw(int money, int wave) {
	reDrawMoney(money);
	reDrawWave(wave);
}

void HUD::reDrawMoney(int money) {
	drawText("TEST"+to_string(money),100,700);
}

void HUD::reDrawWave(int wave) {

}

void HUD::drawText(std::string text, int textCoordX, int textCoordY) {
	SDL_Color text_color;
	text_color.r = 0;
	text_color.g = 0;
	text_color.b = 0;
	text_rect.x = textCoordX;
	text_rect.y = textCoordY;
	text_surface = TTF_RenderUTF8_Solid(fnt, text.c_str(), text_color);
	SDL_BlitSurface(text_surface, NULL, screen, &text_rect);
	SDL_FreeSurface(text_surface);
	text_surface = NULL;
	
}

