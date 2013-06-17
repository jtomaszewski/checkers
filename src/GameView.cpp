/*
 * GameView.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "GameView.h"

GameView::GameView() {
	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return;
	}
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();

	allegro_font = al_load_ttf_font("fonts/Raleway-Medium.ttf", 16, 0);
	allegro_font_big = al_load_ttf_font("fonts/Raleway-Bold.ttf", 40, 0);

	allegro_display = al_create_display(BOARD_WIDTH, BOARD_WIDTH);
	if (!allegro_display) {
		fprintf(stderr, "failed to create display!\n");
		return;
	}

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	cout << "Display started." << endl;
	redraw();
}

GameView::~GameView() {
	al_destroy_display(allegro_display);
	al_destroy_font(allegro_font);
	al_destroy_font(allegro_font_big);
}

void GameView::redraw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));

	if (g->current_player) {
		REP(i, BOARD_SQUARES_SUM)
			drawSquare(g->board->squares[i]);

		if (g->player_win) {
			al_draw_filled_rectangle(30, BOARD_WIDTH / 2 - 20, BOARD_WIDTH - 30, BOARD_WIDTH / 2 + 30, g->player_win->id == PLAYER_TOP ? COLOR_WHITEA : COLOR_BLACKA);
			al_draw_textf(allegro_font_big, g->player_win->id == PLAYER_TOP ? COLOR_BLACK : COLOR_WHITE, BOARD_WIDTH / 2,
					BOARD_WIDTH / 2 - 20, ALLEGRO_ALIGN_CENTRE, "%s won!",
					g->player_win->c_str());
		}
	} else {
		REP(i, BOARD_SQUARES_SUM)
			drawSquare(g->board->squares[i]);
		al_draw_filled_rectangle(0, 0, BOARD_OFFSET_X + BOARD_WIDTH, BOARD_OFFSET_Y + BOARD_WIDTH, COLOR_MENU_BG);

		al_draw_text(allegro_font_big, COLOR_MENU_TEXT, BOARD_WIDTH / 2, 30,
				ALLEGRO_ALIGN_CENTRE, "CHECKERS");
		al_draw_text(allegro_font, COLOR_MENU_TEXT, 30, 100, 0, "Choose your mode:");
		al_draw_text(allegro_font, menu_selection != 1 ? COLOR_MENU_TEXT
				: COLOR_MENU_SELECTED, 30, 130, 0, "1) HUMAN vs HUMAN");
		al_draw_text(allegro_font, menu_selection != 2 ? COLOR_MENU_TEXT
				: COLOR_MENU_SELECTED, 30, 160, 0, "2) HUMAN vs COMPUTER");
		al_draw_text(allegro_font, menu_selection != 3 ? COLOR_MENU_TEXT
				: COLOR_MENU_SELECTED, 30, 190, 0, "3) COMPUTER vs COMPUTER");
		al_draw_text(allegro_font, menu_selection != 4 ? COLOR_MENU_TEXT
				: COLOR_MENU_SELECTED, 30, 230, 0, "4) exit.");
	}

	al_flip_display();
}

void GameView::drawSquare(Square* square) {
	float cx = GET_SQUARE_X(square->x), cy = GET_SQUARE_Y(square->y);

	// square bg
	al_draw_filled_rectangle(cx, cy, cx + SQUARE_WIDTH, cy + SQUARE_WIDTH,
			square->selected ? COLOR_SQUARE_SELECTED
					: (square->possible ? COLOR_SQUARE_POSSIBLE
							: COLOR_SQUARE(square->x, square->y)));

	// piece icon
	if (square->piece) {
		const string filename = string(IMAGES_PATH)
				+ PIECE_TYPE_NAME[square->piece->type] + to_string(
				(int) square->piece->player_id) + ".png";
		ALLEGRO_BITMAP* image = al_load_bitmap(filename.c_str());
		if (image == NULL) {
			fprintf(stderr, "loading of image '%s' failed.\n", filename.c_str());
			return;
		}

		al_draw_bitmap(image, cx, cy, 0);
	}
}
