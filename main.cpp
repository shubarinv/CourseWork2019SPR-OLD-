/* Copyright (C) Vladimir Shubarin - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Vladimir Shubarin <vhundef@gmail.com>, Feb 2019
 */

#include <cstdio>
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include "Game/ship.h"
#include "Game/hud.h"


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
	Ship sh(max_x,max_y);
	bg.w=max_x;
	bg.h=max_y;
	bg.x=0;
	bg.y=0;
	SDL_FillRect(screen,&bg,0x0d34f6);
	HUD hud(screen);
	int i=0;
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
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN) {
				//
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_LEFT) {
				//
			}
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RIGHT) {
				//
			}
		}
		i++;
		hud.reDraw(i,1);
		sh.reDraw(screen);
	}
	SDL_Quit();
	return 0; /* Нормальное завершение */
}