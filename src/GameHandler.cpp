/*
 * GameHandler.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "GameHandler.h"

GameHandler::GameHandler(): game_view(new GameView()) {
	ALLEGRO_THREAD* thread_allegro = al_create_thread(&createAllegroThread, this);
	al_start_thread(thread_allegro);

	al_join_thread(thread_allegro, NULL);
}

GameHandler::~GameHandler() {
	// TODO Auto-generated destructor stub
}

void *GameHandler::createAllegroThread(ALLEGRO_THREAD *thread, void *pointer) {
	cout << "Allegro thread started." << endl;

	GameHandler *self = (GameHandler*) pointer;
	ALLEGRO_DISPLAY *display = g->display->allegro_display;
	al_set_target_bitmap(al_get_backbuffer(display));

	ALLEGRO_EVENT_QUEUE *event_queue;
	bool redraw = true, doexit = false;

	al_install_mouse();
	al_show_mouse_cursor(display);

	al_install_keyboard();

	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	while (1) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		EventResponse event_response;

		switch (ev.type) {
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
		case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
			//				bouncer_x = ev.mouse.x;
			//				bouncer_y = ev.mouse.y;
			break;
		case ALLEGRO_EVENT_KEY_UP:
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				doexit = true;
				break;
			}
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			event_response = self->game_view->handleMouseClick(&ev);
			break;
		}

		switch (event_response.type) {
		case EVENT_SQUARE_SELECT:
			redraw |= self->triggerSelect( g->board->squares[event_response.i] );
			break;
		case EVENT_NONE:
			break;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			self->game_view->redraw();
		}

		if (doexit)
			break;
	}

	al_destroy_event_queue(event_queue);
	return NULL;
}

bool GameHandler::triggerSelect(Square *square) {
	if (square == NULL) { // wymuszamy odznaczenie?
		bool changedSomething = false;
		if (g->selected_square != NULL)
			g->selected_square->selected = false, changedSomething = true;
		g->selected_square = NULL;
		return changedSomething;
	}

	if (g->selected_square == NULL) { // zaznaczamy od nowa
		if (g->force_selected)
			return false;
		if (square->piece && square->piece->player_id == g->current_player->id) {
			g->selectSquare(square);
		} else
			return false;
	} else if (g->selected_square == square) { // zaznaczylismy biezacy - odznaczamy
		if (g->force_selected)
			return false;
		g->selectSquare(NULL);
	} else { // mamy juz swoj zaznaczony; zaznaczamy inny
		if (square->piece && square->piece->player_id == g->current_player->id) { // zaznaczamy inny swoj
			if (g->force_selected)
				return false;
			triggerSelect(NULL);
			triggerSelect(square);
		} else {
//			if (g->selected_square->possible) {
//
//			}
			Move move = Move(g->selected_square, square);
			Move *real_move = g->canMove(&move);
			if (real_move)
				return g->executeMove(real_move);

			return false;
		}
	}

	return true;
}
