/*
 * GameView.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include "../config.h"
#include "Game.h"

class GameView {
public:
	EventResponse handleMouseClick(ALLEGRO_EVENT *ev);
	void redraw();
	void drawSquare(Square* square);
};

#endif /* GAMEVIEW_H_ */
