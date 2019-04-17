//
// Created by vhundef on 17.04.19.
//

#include "ship.h"

using namespace std;

void drawShip(SDL_Surface *where_to_draw, SDL_Rect *shp, SDL_Rect *cleaner, SDL_Rect *ship_tower, SDL_Rect *flag) {
	Sint32 base_color = 0xFFB533; // Основной цвет (желтый)

	SDL_FillRect(where_to_draw, cleaner, 0x0d34f6); // Очищаем экран

	Draw_Line(where_to_draw, shp->x, shp->y, shp->x - 25, shp->y, 0xFFB533);
	Draw_Line(where_to_draw, shp->x, shp->y + shp->h - 1, shp->x - 25, shp->y + shp->h - 20, 0xFFB533);
	SDL_FillRect(where_to_draw, shp, base_color);
	SDL_FillRect(where_to_draw, ship_tower, base_color);
	Draw_Line(where_to_draw, shp->x + 80, shp->y, shp->x + 105, shp->y, 0xFFB533);
	Draw_Line(where_to_draw, shp->x + 80, shp->y + shp->h - 1, shp->x + 105, shp->y + shp->h - 20, 0xFFB533);
	SDL_FillRect(where_to_draw, flag, 0xff7878);

}

void moveShip(SDL_Rect *shipParts[], int leftright, int speed) {
	int ship_towerOffsetX = 0, ship_towerOffsetY = -20, flag_OffsetX = -20, flag_OffsetY = -50;
	//Ship Tower
	shipParts[1]->x = shipParts[0]->x + ship_towerOffsetX;
	shipParts[1]->y = shipParts[0]->y + ship_towerOffsetY;
	//Flag

	if (speed == 0) {
		shipParts[2]->x = shipParts[0]->x + flag_OffsetX + 150;
		shipParts[2]->y = shipParts[0]->y + flag_OffsetY;
	} else {
		if (leftright == 1) {
			shipParts[2]->x = shipParts[0]->x + flag_OffsetX + 5;
			shipParts[2]->y = shipParts[0]->y + flag_OffsetY - 30;
		} else if (leftright == -1) {
			shipParts[2]->x = shipParts[0]->x + flag_OffsetX + 50;
			shipParts[2]->y = shipParts[0]->y + flag_OffsetY - 30;
		}
	}
	if (shipParts[0]->x>1205){
		for (int i = 0; i < 3; ++i) {
			shipParts[i]->x=shipParts[i]->x-1205;
		}
	}
}

Ship::Ship(int max_x, int max_y) {

	r.x = -10;
	r.y = 100;
	r.w = 80;
	r.h = 20;

	cleaner.x=-30;
	cleaner.y=100-40;
	cleaner.h=150;
	cleaner.w=max_x;

	tower.x = max_x / 2;
	tower.y = max_y / 2;
	tower.w = 55;
	tower.h = 20;

	flag.w = 45;
	flag.h = 25;
	r_new = r;

	movementDirrection = 1;
	movementSpeed = 1;
}

void Ship::reDraw(SDL_Surface *screen) {
	// расчет перемещения по горизонтали
	r_new.x = r.x + movementDirrection * movementSpeed; // скорость перемещения и направление движения
	// (на сколько пикселей смещаться за один шаг цикла)

	r = r_new; // обоновляем координаты
	SDL_LockSurface(screen);
	moveShip(shipParts, movementDirrection, movementSpeed);
	drawShip(screen, &r, &cleaner, &tower, &flag);

	//else throw("CANNOT draw");
	SDL_UnlockSurface(screen);
	SDL_UpdateRect(screen, 0, 0, 1280, 720);
	SDL_Delay(movementSpeed * 10); // нужно для замедления движения корабля
}