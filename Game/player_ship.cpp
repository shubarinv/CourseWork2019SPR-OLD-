//
// Created by vhundef on 23.04.19.
//

#include "player_ship.h"

//
// Created by vhundef on 17.04.19.
//
using namespace std;

#include <random>
#include <iostream>
#include <SDL/SDL_draw.h>

int randNum(int min, int max) {
	std::random_device rd;     // only used once to initialise (seed) engine
	std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(min, max); // guaranteed unbiased

	auto random_integer = uni(rng);
	return random_integer;
}

int intlHp;

void PlayerShip::drawShip(SDL_Surface *screen) {

	SDL_FillRect(screen, shipParts[0], 0X0);
	Draw_FillCircle(screen, shipParts[0]->x, shipParts[0]->y + shipParts[0]->h / 2, 18, 0x000000);
	Draw_FillCircle(screen, shipParts[0]->x + shipParts[0]->w, shipParts[0]->y + shipParts[0]->h / 2, 18, 0x000000);
	for (int i = 0; i < intlHp / 20; ++i) {
		if (hitLoc[i] == -999)
			continue;
		Draw_FillCircle(screen, hitLoc[i] + shipParts[0]->x, shipParts[0]->y - 10, 10, 0xFC6600);
	}


}

void PlayerShip::moveShip() {
	if ((shipParts[0]->x >= 1190) && movementDirection == 1) {
		for (int i = 0; i < 3; ++i) {
			shipParts[i]->x = shipParts[i]->x - 1150;
		}

	}
	if ((shipParts[0]->x < 0) && movementDirection == -1) {
		for (int i = 0; i < 3; ++i) {
			shipParts[i]->x = shipParts[i]->x + 1100;
		}
	}
}

PlayerShip::PlayerShip() {
	r.x = randNum(0, 1000);
	r.y = max_y - 75;
	r.w = 90;
	r.h = 35;


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
	movementDirection = 1;
	movementSpeed = 1;
	intlHp = health;
	if (movementSpeed == 3)
		cout << "\n"
		        "............................................   .  .......................................\n"
		        "..........................................88 OM .,..N....................................\n"
		        ".....................................,O.+MMMMMMMMMMMMM.MD................................\n"
		        "................................... =MMMM.MMMMMMMMMMMMMMM,.?.............................\n"
		        "..................................M.MMM,MMMMMMM ZMMMMMMMMMM$$ ...........................\n"
		        ".................................M.MMM.MMMMMM.MMMMMMM,:MMMMM..$N ........................\n"
		        "................................  MMMM+++.:.::: N~.NMMMMMMMMMMMM~M. .....................\n"
		        "................................:.M.................. 8MMMMMN,.ZM+N......................\n"
		        "................................$...................... .MMMMMMMMM.M ....................\n"
		        ".............................. 7..........  .  ..........IDMMMMI:MN.M....................\n"
		        "............................... .. ... ... . .  ~NI...... MMMMMMMMMM I...................\n"
		        "............................. :..?,  .... .... 7D,........ MMMMMMMMMZM...................\n"
		        ".............................M..:8NNMMMMNMMMD8$~...........MM+IDMMMMM.M..................\n"
		        "............................ ............................. 7MMMMMMMMMMMD.................\n"
		        "...........................................................MMMMMMMMMMI7 .................\n"
		        "............................,..............................?MM $MMMMM8M..................\n"
		        "...........................D ..IMMMDMMMN,. .:=: MM?  ......+MMMMMMM8M.7..................\n"
		        "...........................MMMMMMMM .MMMMMMMMMMMMMM. DMM,. MMMMMMMMMM=M..................\n"
		        "...........................MMMMMMMO...MMMMMMMMMMMMM ...   MM: ZMMMMMM:...................\n"
		        "...........................MMMMMMM....ZMMMMMMMMMMM .......MMMM?MIMMZM ...................\n"
		        "...........................M MMMM......OMMMMMMMMM .......MMMM... MM .....................\n"
		        "..........................I...+7 ....... ~~~...... ...... .. ....IM. ....................\n"
		        "..........................:. .....................M=........DM...?M8 ....................\n"
		        "...........................M....I......  ..........M   ..... M.. MO .....................\n"
		        "..........................  ....MM~ZMM  ...........$M.M .....MN. ........................\n"
		        ".........................D~,.......... ............ M.8 ...MO, .Z........................\n"
		        "........................ M .........................7.M .. ..  $.........................\n"
		        "........................ D............................M..  . +, .........................\n"
		        ".........................M... 87 ..  ..MZ............. .... .,...........................\n"
		        ".........................=.. M.MMMMMMMMMM . ................?............................\n"
		        "..........................:.  MMMMMMMMMMMMM.................  ...........................\n"
		        "..........................D...MMMMNMMMMMD,M. ..........MMM=.8 ...........................\n"
		        "............................. :MM=.......D.......... 8..... .,...........................\n"
		        "...........................M..M .. ..  .................... ~............................\n"
		        "...........................:.. DMMMMMMMMMMDI,.........+MN.  .............................\n"
		        "............................$ .... MMMMMM:::.. I....M  .8I~..............................\n"
		        "............................. I ..., .........=.....,D  .................................\n"
		        "..............................O..............M ... 7 ....................................\n"
		        "................ DNNNNNZ.NNNNNNNOIONNNNNNDNNNNNNNNDNNNNNN~.NNNNNM........................\n"
		        "...............,D.......NN ......ZN......:,......N....... NN....N........................\n"
		        "...............N....N...+N ..$~...D......~,......N...,~....N....N........................\n"
		        "...............N....N...~N ..NN...N....N+8, ..N??N ..,N....N....N........................\n"
		        "...............N=....?N:.N ..NN...N....NDM, ..ZOZN...,N... N....N........................\n"
		        "................N~.....~NN....... N......8, .....N...,N... N...:N........................\n"
		        "...............ONNNN....,N...I77NNN....DNM, ..DNNN...,N... N...IN........................\n"
		        "...............N....N....N...N....N....N.O, ..N..N...,N... N,..Z$........................\n"
		        "...............N....D....N...N....N....:::,...:::N...,N... NDDDOD........................\n"
		        "...............O8...  . ON ..N. ..N.......,......N.........N....N........................\n"
		        "................~N8..,DN,DNNNN, ..DNNNNNNNNNNNNNNNNNNNNNNNINNNNNN........................\n"
		        ".................... ....................................................................\n"
		        "........................................................................................." << endl;
	cout << "SPEEEEEEEEEEEEEED=" << movementSpeed << endl;
}

void PlayerShip::reDraw(SDL_Surface *screen) {
	if (health > 0) {
		// расчет перемещения по горизонтали
		r_new.x = r.x + movementDirection * movementSpeed; // скорость перемещения и направление движения
		// (на сколько пикселей смещаться за один шаг цикла)

		r = r_new; // обоновляем координаты

		moveShip();
		drawShip(screen);


	}
}

int PlayerShip::getHealth() const {
	return health;
}

void PlayerShip::setHealth(int hlth) {
	PlayerShip::health = hlth;
}


gameObject::coords PlayerShip::getCoords() {
	location.x1 = shipParts[0]->x - 25;
	location.y1 = shipParts[1]->y;
	location.x2 = shipParts[0]->x + 25 + shipParts[0]->w;
	location.y2 = shipParts[1]->y + shipParts[1]->h + shipParts[0]->h;

	return location;
}

void PlayerShip::spawnHit(int hlc) {
	hitLoc[hitsTaken] = hlc - shipParts[0]->x;
	cout << "Hit loc" << hlc << endl;
	hitsTaken++;
}

void PlayerShip::setMovementSpeed(int movementSpeed) {
	PlayerShip::movementSpeed = movementSpeed;
}

void PlayerShip::setMovementDirection(int movementDirection) {
	PlayerShip::movementDirection = movementDirection;
}

int PlayerShip::getMovementDirection() const {
	return movementDirection;
}


