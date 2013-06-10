/*
 * Display.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "Display.h"

Display::Display() {
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return;
	}
	al_init_image_addon();
	al_init_primitives_addon();

	allegro_display = al_create_display(BOARD_WIDTH, BOARD_WIDTH);
	if (!allegro_display) {
		fprintf(stderr, "failed to create display!\n");
		return;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	cout << "Display started." << endl;
}

Display::~Display() {
	al_destroy_display(allegro_display);
}
