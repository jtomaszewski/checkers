/*
 * Pawn.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "Pawn.h"

Pawn::Pawn() {
	type = PAWN;
}

Squares Pawn::getPossibleSquares(Square** board) {
	Squares squares;

	if (player_id == PLAYER_TOP) {
		INSERT_SQUARE(squares, square->x - 1, square->y + 1, board);
		INSERT_SQUARE(squares, square->x + 1, square->y + 1, board);
	} else {
		INSERT_SQUARE(squares, square->x - 1, square->y - 1, board);
		INSERT_SQUARE(squares, square->x + 1, square->y - 1, board);
	}

	return squares;
}

bool Pawn::isMovePossible(Move *move, Square** board) {
	if (move->to->piece
			&& !IS_ENEMY(move->from, move->to))
		return false;

	return true;
}

Moves Pawn::getPossibleMoves(Square** board) {
	Moves moves;
	Squares squares = getPossibleSquares(board);

	FOREACH(i, squares) {
		Move move = Move(square, *i, MOVE | KILL);
		if (Pawn::isMovePossible(&move, board))
			moves.PB( move );
	}

	return moves;
}
