//
// Created by vhundef on 17.04.19.
//

#ifndef COURSEWORK_GAME_MANAGER_H
#define COURSEWORK_GAME_MANAGER_H


#include <SDL/SDL_video.h>

class GameManager {
private:
	int money=0,wave=0;
	int shots=0,missed=0,hits=0,killedShips=0;
public:
	int getShots() const {
		return shots;
	}

	void setShots(int shots) {
		GameManager::shots = shots;
	}

	int getMissed() const {
		return missed;
	}

	void setMissed(int missed) {
		GameManager::missed = missed;
	}

	int getHits() const {
		return hits;
	}

	void setHits(int hits) {
		GameManager::hits = hits;
	}

	int getKilledShips() const {
		return killedShips;
	}

	void setKilledShips(int killedShips) {
		GameManager::killedShips = killedShips;
	}

private:
	int shipsLeft=0;
public:
	int getWave() const;

	void setWave(int wave);
	int getMoney() const;
	void setMoney(int money);
	GameManager();
	void updateActionRect(SDL_Surface *screen);
	void updatePlayerRect(SDL_Surface *screen);


	int getShipsLeft() const;
	void checkForCollisions();
	void setShipsLeft(int shipsLeft);
};


#endif //COURSEWORK_GAME_MANAGER_H
