/*
 * Piece.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "Piece.h"

Piece::~Piece() {
	square->setPiece(NULL);
}

Moves Piece::getPossibleMoves(Square** board) {
	return Moves();
}
