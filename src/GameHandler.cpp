/*
 * GameHandler.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "GameHandler.h"

GameHandler::GameHandler(): game_view(new GameView()) {
	thread_allegro = al_create_thread(&createAllegroThread, this);
	al_start_thread(thread_allegro);

	al_join_thread(thread_allegro, NULL);
}

GameHandler::~GameHandler() {
	delete g;
	delete game_view;
}

void *GameHandler::createAllegroThread(ALLEGRO_THREAD *thread, void *pointer) {
	cout << "Allegro thread started." << endl;

	GameHandler *self = (GameHandler*) pointer;
	ALLEGRO_DISPLAY *display = self->game_view->allegro_display;
	al_set_target_bitmap(al_get_backbuffer(display));

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(COMPUTER_TURN_TIME);
	bool redraw = true;

	al_install_mouse();
	al_show_mouse_cursor(display);
	al_install_keyboard();

	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	while (1) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		switch (ev.type) {
		case ALLEGRO_EVENT_TIMER:
			if (g->current_player && g->current_player->type == PLAYER_COMPUTER && !g->player_win) {
				if (!g->executeComputerMove())
					break;

				redraw |= true;
			}
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			break;
		case ALLEGRO_EVENT_KEY_UP:
			redraw |= self->handleKeyboard(&ev);
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			redraw |= self->handleMouse(&ev);
			break;
		}

		if (!self->game_view)
			break;

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			self->game_view->redraw();
		}
	}

	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	return NULL;
}

bool GameHandler::handleKeyboard(ALLEGRO_EVENT *ev) {
	if (!g->current_player)
		switch (ev->keyboard.keycode) {
		case ALLEGRO_KEY_1:
			selectMenu(1);
			return true;
			break;
		case ALLEGRO_KEY_2:
			selectMenu(2);
			return true;
			break;
		case ALLEGRO_KEY_3:
			selectMenu(3);
			return true;
			break;
		case ALLEGRO_KEY_4:
			selectMenu(4);
			return true;
			break;
		case ALLEGRO_KEY_ESCAPE:
			delete game_view, game_view = NULL;
			break;
		}
	else // (g)
		switch (ev->keyboard.keycode) {
		case ALLEGRO_KEY_ESCAPE:
			g->current_player = NULL;
			break;
		}

	return false;
}

bool GameHandler::handleMouse(ALLEGRO_EVENT *ev) {
	int ex = ev->mouse.x, ey = ev->mouse.y;

	if (g->current_player) {
		if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP && WITHIN(ex,ey,
				BOARD_OFFSET_X, BOARD_OFFSET_Y,
				BOARD_OFFSET_X + BOARD_WIDTH, BOARD_OFFSET_Y + BOARD_WIDTH)) {
			int	i = SQUARE_WITHIN(ex, ey);

			return selectSquare(g->board->squares[i]);
		}
	} else {
		int menu_selection = 0;
		if (WITHIN(ex,ey,0,130,BOARD_WIDTH,146)) {
			menu_selection = 1;
		} else if (WITHIN(ex,ey,0,160,BOARD_WIDTH,176)) {
			menu_selection = 2;
		} else if (WITHIN(ex,ey,0,190,BOARD_WIDTH,206)) {
			menu_selection = 3;
		} else if (WITHIN(ex,ey,0,230,BOARD_WIDTH,246)) {
			menu_selection = 4;
		}
		if (ev->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
			selectMenu(menu_selection);
			return true;
		}

		if (menu_selection != game_view->menu_selection) {
			game_view->menu_selection = menu_selection;
			return true;
		}
	}

	return false;
}

void GameHandler::selectMenu(int menu_selection) {
	if (g)
		delete g, g = new Game();

	bool human_is_white = (rand() % 100) > 50;
	switch (menu_selection) {
	case 1:
		g->assignPlayers(PLAYER_HUMAN, PLAYER_HUMAN);
		break;
	case 2:
		g->assignPlayers(human_is_white ? PLAYER_COMPUTER : PLAYER_HUMAN, human_is_white ? PLAYER_HUMAN : PLAYER_COMPUTER);
		break;
	case 3:
		g->assignPlayers(PLAYER_COMPUTER, PLAYER_COMPUTER);
		break;
	case 4:
		delete game_view, game_view = NULL;
		break;
	}
}

bool GameHandler::selectSquare(Square *square) {
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
			selectSquare(NULL);
			selectSquare(square);
		} else {
//			if (g->selected_square->possible) {
//
//			}
			Move move = Move(g->selected_square, square);
			Move *real_move = g->canMove(&move);
			if (real_move)
				return g->executeMove(real_move, false);

			return false;
		}
	}

	return true;
}
