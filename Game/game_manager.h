//
// Created by vhundef on 17.04.19.
//

#ifndef COURSEWORK_GAME_MANAGER_H
#define COURSEWORK_GAME_MANAGER_H


#include <SDL/SDL_video.h>

class GameManager {
private:
	int money,wave;

public:
	int getWave() const;

	void setWave(int wave);
	int getMoney() const;
	void setMoney(int money);
	GameManager();
	void updateActionRect(SDL_Surface *screen);
	int shipsLeft=0;
};


#endif //COURSEWORK_GAME_MANAGER_H
