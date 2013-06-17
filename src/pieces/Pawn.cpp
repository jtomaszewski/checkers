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

Pawn::Pawn(Pawn *pawn) {
	type = PAWN;
	player_id = pawn->player_id;
	square = pawn->square, square->piece = this;
}

Pawn::~Pawn() {
	square->setPiece(NULL);
}

bool Pawn::canKill(Square **board) {
	Moves moves = getPossibleKillMoves(board);
	return moves.size() > 0;
}

Moves Pawn::getPossibleMoves(Square** board) {
	Moves moves = getPossibleStepMoves(board);
	Moves moves2 = getPossibleKillMoves(board);
	moves.splice(moves.begin(), moves2);

	return moves;
}

Moves Pawn::getPossibleStepMoves(Square** board) {
	Squares squares;
	Moves moves;

	int xoffset = player_id == PLAYER_TOP ? +1 : -1;
	INSERT_SQUARE(squares, square->x - 1, square->y + xoffset, board);
	INSERT_SQUARE(squares, square->x + 1, square->y + xoffset, board);

	FOREACH (i, squares) {
		Move *move = new Move(square, *i);
		if (move->to->piece == NULL) {
			moves.push_back(move), move->full_move = true;
		}
	}

	return moves;
}

Moves Pawn::getPossibleKillMoves(Square **board) {
	// początkowym ruchem dla getPossibleKillMoves jest ruch w miejscu
	Move *kill_move = new Move(square, square);
	return getPossibleKillMoves(board, kill_move, square);
}

Moves Pawn::getPossibleKillMoves(Square **board, Move *move, Square *jumped_from) {
	Moves moves;

	move->full_move = true;
	pii offset[4] = {pii(1,1), pii(1,-1), pii(-1,-1), pii(-1, 1)};
	REP(i, 4) {
		int ax = offset[i].first, ay = offset[i].second;
		if (!CORRECTXY(move->to->x + 2*ax, move->to->y + 2*ay))
			continue;
		Square* enemy_square = board[SQUARE_XYTOI(move->to->x + ax, move->to->y + ay)];
		Square* jump_square = board[SQUARE_XYTOI(move->to->x + 2*ax, move->to->y + 2*ay)];

		if (enemy_square->piece && IS_ENEMY(enemy_square, move->from) && !enemy_square->piece->killed && !jump_square->piece) { // skok możliwy
			Move *move_copy = new Move(*move);
			move_copy->killed_pieces.push_back(enemy_square->piece),
					enemy_square->piece->killed = true,
					move_copy->to = jump_square;
			moves.splice(moves.begin(), getPossibleKillMoves(board, move_copy, move->to));
			if (moves.size() > 0)
				move->full_move = false;
			enemy_square->piece->killed = false;
		}
	}

	if (move->killed_pieces.size() > 0)
		moves.push_back(move);

	return moves;
}
