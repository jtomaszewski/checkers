/*
 * Square.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "Square.h"

Square::Square(const int i) {
	x = SQUARE_ITOX(i);
	y = SQUARE_ITOY(i);
}

void Square::setPiece(Piece* piece) {
	this->piece = piece;
	if (piece != NULL) {
		piece->square = this;
	}
}

const char *Square::c_str() {
	char *str = new char[3];
	sprintf(str, "%c%d", (char)(x+65), BOARD_COLS - y);

	return str;
}
