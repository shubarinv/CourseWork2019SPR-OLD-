/* Copyright (C) Vladimir Shubarin - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Vladimir Shubarin <vhundef@gmail.com>, Feb 2019
 */

#include <cstdio>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <iostream>
#include <caca_conio.h>
#include "Game/ship.h"
#include "Game/hud.h"
#include "Game/game_manager.h"
#include "Game/weapon.h"
#include "Game/player_ship.h"

int main(int argc, char *argv[]) {
	SDL_WM_SetCaption("Курсовая PRE_ALPHA 0014", nullptr);
	SDL_Surface *screen, *playerArea, *actionArea, *neutralZone; /* объявление указателя на поверхность: */
	SDL_Event event;
	SDL_Rect bg;
	Sint16 max_x, max_y;
	int nextstep = 1; /* для цикла обработки сообщений */
	max_x = 1280;
	max_y = 720;
	screen = SDL_SetVideoMode(max_x, max_y, 32,
	                          SDL_HWSURFACE | SDL_DOUBLEBUF);    /* инициализация библиотеки и установка видеорежима */
	if (!screen) {
		fprintf(stderr, "SDL mode failed: %s\n", SDL_GetError());
		SDL_Quit();
		return 1; /* Выход с одним кодом ошибки */
	}

	playerArea = SDL_CreateRGBSurface(SDL_HWSURFACE |
	                                  SDL_DOUBLEBUF, max_x, 80, 16,
	                                  screen->format->Rmask, screen->format->Gmask,
	                                  screen->format->Bmask, screen->format->Amask);
	actionArea = SDL_CreateRGBSurface(SDL_HWSURFACE |
	                                  SDL_DOUBLEBUF, max_x, 120, 16,
	                                  screen->format->Rmask, screen->format->Gmask,
	                                  screen->format->Bmask, screen->format->Amask);
	neutralZone = SDL_CreateRGBSurface(SDL_HWSURFACE |
	                                   SDL_DOUBLEBUF, max_x, max_y-80, 8,
	                                   screen->format->Rmask, screen->format->Gmask,
	                                   screen->format->Bmask, screen->format->Amask);
	if (!(playerArea && actionArea && neutralZone)) {
		cout << "Unable to create temporary surfaces: %s\n" << SDL_GetError() << endl;
		return -3;
	}
	bg.w = max_x;
	bg.h = max_y;
	bg.x = 0;
	bg.y = 120;
	HUD hud(screen);
	Weapon weapon(screen, max_x, max_y);
	GameManager gm;
	gm.setMoney(60);
	Ship *ships = nullptr;
	PlayerShip player;
	while (nextstep > 0) // цикл перерисовки и обработки событий
	{
		SDL_FillRect(neutralZone, &bg, 0x0d34f6);
		SDL_BlitSurface(neutralZone, nullptr,screen, nullptr);
		SDL_BlitSurface(actionArea,nullptr,screen, nullptr);


		if (gm.getMoney() < 0)
			nextstep = -999;
		if (SDL_PollEvent(&event)) // проверяем нажатие клавиш на клавиатуре
		{
			if (event.type == SDL_QUIT ||
			    (event.type == SDL_KEYDOWN &&
			     event.key.keysym.sym == SDLK_ESCAPE))
				nextstep = 0;
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE) {
				weapon.shoot((player.getCoords().x1 + player.getCoords().x2) / 2);
				gm.setMoney(gm.getMoney() - 5);
				gm.setShots(gm.getShots() + 1);
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
				player.setMovementSpeed(0);
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP) {
				player.setMovementSpeed(1);
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT) {
				player.setMovementDirection(-1);
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT) {
				player.setMovementDirection(1);
			}
		}
		gm.updateActionRect(actionArea);
		hud.reDraw(gm.getMoney(), gm.getWave());
		weapon.updateParticles();

		//IF no ships left
		if (gm.getShipsLeft() <= 0) {
			gm.setWave(gm.getWave() + 1);
			gm.setShipsLeft(gm.getWave() * 2);
			weapon.reset(gm.getWave());
			delete[] ships;
			cout << "spwn: " << gm.getWave() * 2 << endl;
			ships = new Ship[gm.getWave() * 2];
		}

		//Ships redraw
		for (int j = 0; j < gm.getWave() * 2; ++j) {
			if (ships[j].getHealth() > 0) {
				int hits = weapon.checkCollisions(ships[j].getCoords());
				ships[j].setHealth(ships[j].getHealth() - hits * 25);
				gm.setMoney(gm.getMoney() + 15 * hits);
				if (hits > 0) {
					gm.setHits(gm.getHits() + hits);
					ships[j].spawnHit(weapon.getHitLoc());
					cout << "Ship: " << j << "\t" << "Hits: " << hits << endl;
					cout << "Ship: " << j << "HP: " << ships[j].getHealth() << endl;
					if (ships[j].getHealth() <= 0) {
						gm.setShipsLeft(gm.getShipsLeft() - 1);
						gm.setKilledShips(gm.getKilledShips() + 1);
					}
				}
				ships[j].reDraw(screen);
			}
		}
		gm.updatePlayerRect(screen);

		player.reDraw(screen);

		SDL_UpdateRect(screen, 0, 0, 1280, 720);
		SDL_Delay(10); // нужно для замедления движения корабля

	}



	/*-------------------------*/
	if (nextstep == -999) {
		SDL_Rect gmOver;
		gmOver.x = max_x / 2 - 400;
		gmOver.y = max_y / 2 - 60;
		gmOver.h = 120;
		gmOver.w = 800;
		SDL_FillRect(screen, &gmOver, 0xFF12121);
		hud.drawText("GAME OVER!", max_x / 2 - 40, max_y / 2 - 10);
		hud.drawText("Press ESC to show stats", max_x / 2 - 95, max_y / 2 + 30);
		SDL_UpdateRect(screen, 0, 0, 1280, 720);
		while (true)
			if (SDL_PollEvent(&event))
				if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
					break;
		gmOver.x = 0;
		gmOver.y = 0;
		gmOver.h = max_y;
		gmOver.w = max_x;
		SDL_FillRect(screen, &gmOver, 0x000000);
		hud.drawText("Stats", max_x / 2, 70);
		hud.drawText("Ships killed:  " + to_string(gm.getKilledShips()), 100, 100);
		hud.drawText("Waves survived:  " + to_string(gm.getWave()), 100, 130);
		hud.drawText("Hits:  " + to_string(gm.getHits()), 100, 160);
		hud.drawText("Misses:  " + to_string(gm.getShots() - gm.getHits()), 100, 190);
		hud.drawText("Accuracy:  " + to_string((float) gm.getHits() / (gm.getShots() - gm.getHits())) + "%", 100, 220);
		hud.drawText("ESC to Quit", max_x / 2 - 20, max_y - 100);

		SDL_UpdateRect(screen, 0, 0, 1280, 720);

		while (true)
			if (SDL_PollEvent(&event))
				if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
					break;

	}


	SDL_Quit();

	return 0; /* Нормальное завершение */
}
/*
 * Update 11 plan
 * add player ship
 * let player control it
 */

/*
 * Update 12 plan
 * attach weapon to ship
 */

/* Update 13 plan
 * stats
 */