//
// Created by vhundef on 17.04.19.
//

#include "ship.h"

using namespace std;

#include <random>
#include <iostream>

int ranNum(int min, int max) {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	auto random_integer = uni(rng);
	return random_integer;
}

int hp;

void drawShip(SDL_Surface *where_to_draw, SDL_Rect *shp, SDL_Rect *ship_tower, SDL_Rect *flag, int *hitLoc) {
	Sint32 base_color = 0xFFB533; // Основной цвет (желтый)

	Draw_Line(where_to_draw, shp->x, shp->y, shp->x - 25, shp->y, 0xFFB533);
	Draw_Line(where_to_draw, shp->x, shp->y + shp->h - 1, shp->x - 25, shp->y + shp->h - 20, 0xFFB533);
	SDL_FillRect(where_to_draw, shp, base_color);
	SDL_FillRect(where_to_draw, ship_tower, base_color);
	Draw_Line(where_to_draw, shp->x + 80, shp->y, shp->x + 105, shp->y, 0xFFB533);
	Draw_Line(where_to_draw, shp->x + 80, shp->y + shp->h - 1, shp->x + 105, shp->y + shp->h - 20, 0xFFB533);
	Draw_Line(where_to_draw, shp->x + 30, shp->y + shp->h - 1, shp->x + 30, shp->y + shp->h - 100, 0xFFB533);
	SDL_FillRect(where_to_draw, flag, 0xff7878);

	for (int i = 0; i < hp / 20; ++i) {
		if (hitLoc[i] == -999)
			continue;
		Draw_FillCircle(where_to_draw, hitLoc[i] + shp->x, shp->y + 10, 10, 0xff1100);
		Draw_FillCircle(where_to_draw, hitLoc[i] + shp->x, shp->y + 10, 9, 0xff2f00);
		Draw_FillCircle(where_to_draw, hitLoc[i] + shp->x, shp->y + 10, 8, 0xff4400);
		Draw_FillCircle(where_to_draw, hitLoc[i] + shp->x, shp->y + 10, 7, 0xff7e14);
		Draw_FillCircle(where_to_draw, hitLoc[i] + shp->x, shp->y + 10, 6, 0xffaa3b);
		Draw_FillCircle(where_to_draw, hitLoc[i] + shp->x, shp->y + 10, 5, 0xffba52);
		Draw_FillCircle(where_to_draw, hitLoc[i] + shp->x, shp->y + 10, 4, 0xfcde65);
	}


}

void Ship::moveShip(SDL_Rect *shipParts[], int leftright, int speed) {

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
			shipParts[2]->x = shipParts[0]->x + flag_OffsetX + 20;
			shipParts[2]->y = shipParts[0]->y + flag_OffsetY - 30;
		} else if (leftright == -1) {
			shipParts[2]->x = shipParts[0]->x + flag_OffsetX + 50;
			shipParts[2]->y = shipParts[0]->y + flag_OffsetY - 30;
		}
	}
	if ((shipParts[0]->x >= 1190) && leftright == 1) {
		for (int i = 0; i < 3; ++i) {
			shipParts[i]->x = shipParts[i]->x - 1150;
		}

	}

	if ((shipParts[0]->x < 0) && leftright == -1) {
		for (int i = 0; i < 3; ++i) {
			shipParts[i]->x = shipParts[i]->x + 1100;
		}
	}
	if (shipParts[0]->x == propSpeedLoc) {
		movementSpeed = ranNum(1, 3);
		maxSpeed=movementSpeed;
		propSpeedLoc = ranNum(100, 600);
		movementDirrection = ranNum(-1, 1);
		if (movementDirrection == 0)movementDirrection = 1;
		cout << "Increase now at " << propSpeedLoc << endl;
	}

}

Ship::Ship() {
	r.x = ranNum(0, 1000);
	r.y = 100;
	r.w = 80;
	r.h = 20;

	bAllowedToShoot = true;

	tower.x = max_x / 2;
	tower.y = max_y / 2;
	tower.w = 55;
	tower.h = 20;

	flag.w = 30;
	flag.h = 15;
	r_new = r;

	health = 100;
	hitLoc = new int[health / 20];
	for (int i = 0; i < health / 20; ++i) {
		hitLoc[i] = -999;
	}
	movementDirrection = ranNum(-1, 1);
	if (movementDirrection == 0)movementDirrection = 1;
	movementSpeed = ranNum(1, 3);
	maxSpeed=movementSpeed;
	hp = health;
	propSpeedLoc = ranNum(140, 680);
	cout << "SPEEEEEEEEEEEEEED=" << movementSpeed << endl;

}

long int itr = 0;
int shots = 0;

void Ship::reDraw(coords shp) {
	if (health > 0) {
		itr++;
		// расчет перемещения по горизонтали
		r_new.x = r.x + movementDirrection * movementSpeed; // скорость перемещения и направление движения
		// (на сколько пикселей смещаться за один шаг цикла)

		r = r_new; // обоновляем координаты

		moveShip(shipParts, movementDirrection, movementSpeed);
		drawShip(screen, &r, &tower, &flag, hitLoc);

		if (abs((shp.x1 + shp.x2) / 2 - (location.x1 + location.x2) / 2) >= 20 &&
		    (abs((shp.x1 + shp.x2) / 2 - (location.x1 + location.x2) / 2) <= 240)) {
			if (itr % 40 == 0 && shots <= 84) {
				if (isBAllowedToShoot()) {
					weapon.shoot((location.x1 + location.x2) / 2, (location.y1 + location.y2) / 2);
					shots++;
				}
			}

		}
		weapon.updateParticles();

	}
}

int Ship::getHealth() const {
	return health;
}

void Ship::setHealth(int hp) {
	Ship::health = hp;
}

gameObject::coords Ship::getCoords() {
	location.x1 = shipParts[0]->x - 25;
	location.y1 = shipParts[1]->y;
	location.x2 = shipParts[0]->x + 25 + shipParts[0]->w;
	location.y2 = shipParts[1]->y + shipParts[1]->h + shipParts[0]->h;

	return location;
}

void Ship::spawnHit(int hlc) {
	hitLoc[hitsTaken] = hlc - shipParts[0]->x;
	cout << "Hit loc" << hlc << endl;
	hitsTaken++;
}

void Ship::setScreen(SDL_Surface *scrn) {
	screen = scrn;
	setWeapon(Weapon(screen, 1280, 720, false));
	weapon.reset(2);
	// total of 84 shots
}

void Ship::setWeapon(const Weapon &weapon) {
	Ship::weapon = weapon;
}

bool Ship::isBAllowedToShoot() const {
	return bAllowedToShoot;
}

void Ship::setBAllowedToShoot(bool AllowedToShoot) {
	cout<<"Allowed to shoot is now: "<<AllowedToShoot<<endl;
	Ship::bAllowedToShoot = AllowedToShoot;
}

void Ship::setMovementSpeed(int movementSpeed) {
	Ship::movementSpeed = movementSpeed;
}

int Ship::getMaxSpeed() const {
	return maxSpeed;
}


