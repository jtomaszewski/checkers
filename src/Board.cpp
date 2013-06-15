/*
 * Board.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "Board.h"

PIECE_TYPE Board::DEFAULT_SETUP[] = {
		PAWN,    NOTHING, PAWN,    NOTHING, PAWN,    NOTHING, PAWN,    NOTHING,
		NOTHING, PAWN,    NOTHING, PAWN,    NOTHING, PAWN,    NOTHING, PAWN,
		PAWN,    NOTHING, PAWN,    NOTHING, PAWN,    NOTHING, PAWN,    NOTHING,
		NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
		NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING, NOTHING,
		NOTHING, PAWN,    NOTHING, PAWN,    NOTHING, PAWN,    NOTHING, PAWN,
		PAWN,    NOTHING, PAWN,    NOTHING, PAWN,    NOTHING, PAWN,    NOTHING,
		NOTHING, PAWN,    NOTHING, PAWN,    NOTHING, PAWN,    NOTHING, PAWN,
};

Board::Board() {

}

Board::~Board() {
	for (int i = 0; i < BOARD_SQUARES_SUM; i++)
		delete squares[i];
}

void Board::assignSquaresAndPieces() {
	for (int i = 0; i < BOARD_SQUARES_SUM; i++) {
		Piece *piece = createPiece(Board::DEFAULT_SETUP[i]);
		if (piece) {
			piece->player_id = i < BOARD_SQUARES_SUM / 2 ? PLAYER_TOP
					: PLAYER_BOTTOM;
		}

		Square* square = squares[i] = new Square(i);
		square->setPiece(piece);
	}
}

Piece *Board::createPiece(PIECE_TYPE type) {
	switch (type) {
	case NOTHING:
		return NULL;
	case PAWN:
		return new Pawn();
	case QUEEN:
		return new Queen();
	}

	return 0;
}
