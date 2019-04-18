//
// Created by vhundef on 17.04.19.
//

#include "game_manager.h"

SDL_Rect actionZoneCleaner;
int GameManager::getMoney() const {
	return money;
}

void GameManager::setMoney(int mn) {
	GameManager::money = mn;
}

GameManager::GameManager() {
	money = 0;
	wave=0;
	actionZoneCleaner.h=120;
	actionZoneCleaner.w=1280;
	shipsLeft=0;
}

int GameManager::getWave() const {
	return wave;
}

void GameManager::setWave(int wv) {
	GameManager::wave = wv;
}

void GameManager::updateActionRect(SDL_Surface *screen) {
	SDL_FillRect(screen,&actionZoneCleaner,0x0d34f6);
}

int GameManager::getShipsLeft() const {
	return shipsLeft;
}

void GameManager::setShipsLeft(int shpsL) {
	GameManager::shipsLeft = shpsL;
}
