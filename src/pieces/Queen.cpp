/*
 * Queen.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "Queen.h"

Queen::Queen() {
	type = QUEEN;
}

Queen::Queen(Pawn *pawn) {
	type = QUEEN;
	player_id = pawn->player_id;
	square = pawn->square, square->piece = this;
}


Moves Queen::getPossibleStepMoves(Square** board) {
	Squares squares;
	Moves moves;

	int offsets[][2] = { {1,1}, {1,-1}, {-1,-1}, {-1,1} };
	REP(i, 4) {
		int ax = offsets[i][0], ay = offsets[i][1];
		int px = square->x + ax, py = square->y + ay;
		while (CORRECTXY(px, py)) {
			Square *sq = board[SQUARE_XYTOI(px,py)];
			if (sq->piece)
				break;
			Move *move = new Move(square, sq);
			moves.push_back(move), move->full_move = true;

			px += ax, py += ay;
		}
	}

	return moves;
}

Moves Queen::getPossibleKillMoves(Square **board) {
	// początkowym ruchem dla getPossibleKillMoves jest ruch w miejscu
	Move *kill_move = new Move(square, square);
	return getPossibleKillMoves(board, kill_move, pii(0,0));
}

Moves Queen::getPossibleKillMoves(Square **board, Move *move, pii jumped_from_offset) {
	Moves moves;

	move->full_move = true;
	pii offsets[] = { {1,1}, {1,-1}, {-1,-1}, {-1,1} };
	REP(i, 4) { // dla każdego kierunku..
		int ax = offsets[i].first, ay = offsets[i].second;
		int px = square->x + ax, py = square->y + ay;

		if (jumped_from_offset.first == -ax && jumped_from_offset.second == -ay) // nie mozna skoczyc w ta i z powrotem
			continue;

		while (CORRECTXY(px, py)) { // .. powtarzamy aż natrafimy na wrogiego pionka
			Square *enemy_square = board[SQUARE_XYTOI(px, py)];
			if (!enemy_square->piece) {
				px += ax, py += ay;
				continue;
			}

			if (!IS_ENEMY(enemy_square, move->from) || enemy_square->piece->killed)
				break;

			int jx = px + ax, jy = py + ay;
			while (CORRECTXY(jx, jy)) { // .. i wskakujemy "za" niego w dowolne puste pole przed następnym pionkiem w linii
				Square *jump_square = board[SQUARE_XYTOI(jx,jy)];
				if (jump_square->piece)
					break;

				Move *move_copy = new Move(*move);
				move_copy->killed_pieces.push_back(enemy_square->piece),
						enemy_square->piece->killed = true,
						move_copy->to = jump_square;
				moves.splice(moves.begin(), getPossibleKillMoves(board, move_copy, offsets[i]));
				if (moves.size() > 0)
					move->full_move = false;
				enemy_square->piece->killed = false;

				jx += ax, jy += ay;
			}
			break;
		}
	}

	if (move->killed_pieces.size() > 0)
		moves.push_back(move);

	return moves;
}
