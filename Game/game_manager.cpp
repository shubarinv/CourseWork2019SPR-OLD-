//
// Created by vhundef on 17.04.19.
//

#include "game_manager.h"
#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>

SDL_Rect actionZoneCleaner;
SDL_Rect playerZoneCleaner;
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

	playerZoneCleaner.y=720-80;
	playerZoneCleaner.w=1280;
	playerZoneCleaner.h=80;
	shipsLeft=0;
}

int GameManager::getWave() const {
	return wave;
}

void GameManager::setWave(int wv) {
	GameManager::wave = wv;
}

void GameManager::updateActionRect(SDL_Surface *screen) {
	SDL_FillRect(screen,&actionZoneCleaner,0x9ed3ff);
	for (int i = 0; i < 1280; i+=20) {
		Draw_FillCircle(screen,i,125,20,0x0d34f6);
	}
}

int GameManager::getShipsLeft() const {
	return shipsLeft;
}

void GameManager::setShipsLeft(int shpsL) {
	GameManager::shipsLeft = shpsL;
}

void GameManager::updatePlayerRect(SDL_Surface *screen) {
	SDL_FillRect(screen,&playerZoneCleaner,0x0d34f6);
}
