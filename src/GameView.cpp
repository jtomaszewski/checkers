/*
 * GameView.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "GameView.h"

EventResponse GameView::handleMouseClick(ALLEGRO_EVENT *ev) {
	int ex = ev->mouse.x, ey = ev->mouse.y;

	if (WITHIN(ex,ey,
			BOARD_OFFSET_X, BOARD_OFFSET_Y,
			BOARD_OFFSET_X + BOARD_WIDTH, BOARD_OFFSET_Y + BOARD_WIDTH)) {
		int	i = SQUARE_WITHIN(ex, ey);

		return EventResponse(EVENT_SQUARE_SELECT, i);
	}

	return EventResponse();
}

void GameView::redraw() {
	al_clear_to_color(al_map_rgb(0, 0, 0));

	for (int i = 0; i < BOARD_SQUARES_SUM; i++) {
		drawSquare(g->board->squares[i]);
	}

	al_flip_display();
}

void GameView::drawSquare(Square* square) {
	float cx = GET_SQUARE_X(square->x), cy = GET_SQUARE_Y(square->y);

	bool possible = false;
	if (g->selected_square != NULL && g->selected_square->piece) {
		Moves possible_moves = g->selected_square->piece->getPossibleMoves(g->board->squares);
		FOREACH(i, possible_moves) {
			if ((*i).to == square) {
				possible = true;
				break;
			}
		}
	}

	// square bg
	al_draw_filled_rectangle(cx, cy, cx + SQUARE_WIDTH, cy + SQUARE_WIDTH,
			square->selected ? COLOR_SQUARE_SELECTED : (possible ? COLOR_SQUARE_POSSIBLE : COLOR_SQUARE(square->x, square->y)));

	// piece icon
	if (square->piece) {
		const string filename = string(PIECES_PATH)
				+ PIECE_NAMES[square->piece->type] + to_string(
				(int) square->piece->player_id) + ".png";
		ALLEGRO_BITMAP* image = al_load_bitmap(filename.c_str());
		if (image == NULL) {
			fprintf(stderr, "loading of image '%s' failed.\n", filename.c_str());
			return;
		}

		al_draw_bitmap(image, cx, cy, 0);
	}
}
