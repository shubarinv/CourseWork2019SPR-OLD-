//
// Created by vhundef on 17.04.19.
//

#ifndef COURCEWORK_HUD_H
#define COURCEWORK_HUD_H

#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include <SDL/SDL_ttf.h>
#include <string>

using namespace std;
class HUD {
public:
	HUD(SDL_Surface*);

	void reDraw(int, int);

	void drawText(string text, int textCoordX, int textCoordY);

private:
	void reDrawMoney(int);

	void reDrawWave(int);

	TTF_Font *fnt = NULL;
	SDL_Rect text_rect;
	SDL_Color text_color;
	SDL_Surface *text_surface = nullptr;
	SDL_Surface * screen;
};


#endif //COURCEWORK_HUD_H
