/* Copyright (C) Vladimir Shubarin - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Vladimir Shubarin <vhundef@gmail.com>, Feb 2019
 */

#include <cstdio>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <iostream>
#include "Game/ship.h"
#include "Game/hud.h"
#include "Game/game_manager.h"
#include "Game/weapon.h"


int main(int argc, char *argv[]) {
	SDL_Surface *screen; /* объявление указателя на поверхность: */
	SDL_Event event;
	SDL_Rect bg;
	Sint16 max_x, max_y;
	int nextstep = 1; /* для цикла обработки сообщений */
	max_x = 1280;
	max_y = 720;
	screen = SDL_SetVideoMode(max_x, max_y, 32,
	                          SDL_ANYFORMAT);    /* инициализация библиотеки и установка видеорежима */
	if (!screen) {
		fprintf(stderr, "SDL mode failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 1; /* Выход с одним кодом ошибки */
	}
	bg.w = max_x;
	bg.h = max_y;
	bg.x = 0;
	bg.y = 0;
	SDL_FillRect(screen, &bg, 0x0d34f6);
	bg.w = 6;
	bg.h = max_y - 120;
	bg.x = max_x / 2 - 1;
	bg.y = 120;
	HUD hud(screen);
	Weapon weapon(screen, max_x, max_y);
	GameManager gm;
	gm.setMoney(100);
	Ship *ships = nullptr;
	while (nextstep) // цикл перерисовки и обработки событий
	{

		if (SDL_PollEvent(&event)) // проверяем нажатие клавиш на клавиатуре
		{
			if (event.type == SDL_QUIT ||
			    (event.type == SDL_KEYDOWN &&
			     event.key.keysym.sym == SDLK_ESCAPE))
				nextstep = 0;
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) {
				//
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE) {
				weapon.shoot();
				gm.setMoney(gm.getMoney() - 10);
				if (gm.getMoney() < 0)
					hud.drawText("CONgRAts Вас отчислили за растрату гос имущества", max_x / 2 - 200, max_y / 2);
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_k) {
				ships[1].setHealth(-1);
				gm.setShipsLeft(gm.getShipsLeft() - 1);
				gm.setMoney(gm.getMoney() + 20);
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
				gm.setShipsLeft(-1);
			}
		}
		gm.updateActionRect(screen);
		hud.reDraw(gm.getMoney(), gm.getWave());
		weapon.updateParticles();
		if (gm.getShipsLeft() <= 0) {
			gm.setWave(gm.getWave() + 1);
			gm.setShipsLeft(gm.getWave() * 2);
			weapon.reset(gm.getWave());
			delete[] ships;
			cout << "spwn: " << gm.getWave() * 2 << endl;
			ships = new Ship[gm.getWave() * 2];
		}
		for (int j = 0; j < gm.getWave() * 2; ++j) {
			ships[j].reDraw(screen);
		}
		SDL_UpdateRect(screen, 0, 0, 1280, 720);
		SDL_Delay(10); // нужно для замедления движения корабля
		SDL_FillRect(screen, &bg, 0x0d34f6);
	}
	SDL_Quit();

	return 0; /* Нормальное завершение */
}