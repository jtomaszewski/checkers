/*
 * GameHandler.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef GAMEHANDLER_H_
#define GAMEHANDLER_H_

class GameHandler;
#include "Game.h"
#include "GameView.h"

class GameHandler {
public:
	GameView *game_view;
	GameHandler();
	virtual ~GameHandler();
	static void* createAllegroThread(ALLEGRO_THREAD* thread, void* pointer);
	bool triggerSelect(Square *square);
};

#endif /* GAMEHANDLER_H_ */
