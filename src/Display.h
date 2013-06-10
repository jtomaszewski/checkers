/*
 * Display.h
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../config.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

class Display {
public:
	ALLEGRO_DISPLAY *allegro_display;
	Display();
	virtual ~Display();
	void redraw();
};

#endif /* DISPLAY_H_ */
