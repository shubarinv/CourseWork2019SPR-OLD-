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
	if (!(fnt = TTF_OpenFont("Roboto-Regular.ttf", 20))) {
		TTF_Quit();
		SDL_Quit();
		throw;
	}
	text_color.r = 0;
	text_color.g = 0;
	text_color.b = 0;

	screen = scrn;
}


void HUD::reDraw(int money, int wave) {
	SDL_FillRect(screen, &money_rect, 0x0);
	SDL_FillRect(screen, &wave_rect, 0x0);
	reDrawMoney(money);
	reDrawWave(wave);

}

void HUD::reDrawMoney(int money) {
	drawText("Money: " + to_string(money), 1, 685,true);
}

void HUD::reDrawWave(int wave) {
	drawText("Wave: " + to_string(wave), 1176, 685, false);
}

void HUD::drawText(std::string text, int textCoordX, int textCoordY, bool isMoney) {
	text_color.r = 255;
	text_color.g = 255;
	text_color.b = 255;
	if (isMoney) {
		money_rect.x = textCoordX;
		money_rect.y = textCoordY;
	} else {
		wave_rect.x = textCoordX;
		wave_rect.y = textCoordY;
	}
	text_surface = TTF_RenderUTF8_Solid(fnt, text.c_str(), text_color);
	if (isMoney)
		SDL_BlitSurface(text_surface, nullptr, screen, &money_rect);
	else
		SDL_BlitSurface(text_surface, nullptr, screen, &wave_rect);
	SDL_FreeSurface(text_surface);
	text_surface = nullptr;
}

