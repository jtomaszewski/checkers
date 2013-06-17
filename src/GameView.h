/*
 * GameView.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef GAMEVIEW_H_
#define GAMEVIEW_H_

#include "../config.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "Game.h"

class GameView {
public:
	ALLEGRO_DISPLAY *allegro_display;
	ALLEGRO_FONT *allegro_font, *allegro_font_big;

	int menu_selection;

	GameView();
	~GameView();
	void redraw();
	void drawSquare(Square* square);
};

#endif /* GAMEVIEW_H_ */
