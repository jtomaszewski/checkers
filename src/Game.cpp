/*
 * Game.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "Game.h"

Game::Game() {
	display = new Display();
	board = new Board();

	board->assignSquaresAndPieces();
	assignPlayers();
}

Game::~Game() {
	delete display;
	delete board;
	delete player1;
	delete player2;
	current_player = NULL;
}

void Game::assignPlayers() {
	player1 = new HumanPlayer();
	player1->id = PLAYER_TOP;

	player2 = new HumanPlayer();
	player2->id = PLAYER_BOTTOM;

	current_player = player2->id == PLAYER_BOTTOM ? player2 : player1;
}

void Game::selectSquare(Square *square) {
	if (selected_square)
		selected_square->selected = false;

	if (square != NULL)
		square->selected = true;

	selected_square = square;

	markPossibleSquares();
}

Moves Game::getAllPossibleMoves(PLAYER_ID player) {
	Moves moves;

	for(int i=0; i<BOARD_SQUARES_SUM; i++) {
		if (board->squares[i]->piece && board->squares[i]->piece->player_id == player) {
			Moves moves2 = board->squares[i]->piece->getPossibleMoves(board->squares);
			moves.splice(moves.begin(), moves2);
		}
	}

	return moves;
}

Move* Game::canMove(Move *move) {
	Moves available_moves = move->from->piece->getPossibleMoves(board->squares);
	FOREACH (m, available_moves) {
		Move *m1 = *m;
		if (*m1 == *move && m1->isSingleStep())
			return *m;
	}

	return NULL;
}

bool Game::executeMove(Move *move) {
	if (!move->to->possible)
		return false;

	FOREACH(i, move->killed_pieces) {
		delete *&*i;
	}

	move->to->setPiece(move->from->piece);
	move->from->setPiece(NULL);

	if (move->isKillingMove()) {
		if (move->to->piece->canKill(board->squares)) { // jeśli z tego ruchu możemy wykonać jeszcze dalsze bicie, kontynuujemy ten ruch
			selectSquare(move->to);
			force_selected = true;
			printf("dokończ ruch.\n");
		} else { // w przeciwnym wypadku kończymy ruch
			force_selected = false;
		}
	}

	if (!force_selected) {
		tryQueenTransform(move->to->piece);
		selectSquare(NULL);
		changeTurn();
	}

	return true;
}

bool Game::hasKillingMove(PLAYER_ID player_id) {
	Moves moves = getAllPossibleMoves(player_id);

	FOREACH (i, moves) {
		if ( (*i)->killed_pieces.size() ) {
			return true;
		}
	}

	return false;
}

void Game::changeTurn() {
	current_player = current_player == player1 ? player2 : player1;
	must_kill = hasKillingMove(current_player->id);
	if (must_kill)
		printf("masz bicie! musisz zbić jednego z pionków wroga.\n");
}

void Game::markPossibleSquares() {
	for(int i=0; i<BOARD_SQUARES_SUM; i++)
		board->squares[i]->possible = false;

	if (selected_square != NULL && selected_square->piece) {
		Moves possible_moves = selected_square->piece->getPossibleMoves(board->squares);
		FOREACH(i, possible_moves) {
			Move *move = *i;
			if (!move->isSingleStep())
				continue;
			if ((force_selected || must_kill) && !move->isKillingMove())
				continue;
			move->to->possible = true;
		}
	}
}

bool Game::tryQueenTransform(Pawn *pawn) {
	if (pawn->type != PAWN)
		return false;

	if ((pawn->square->y == 0 && pawn->player_id == PLAYER_BOTTOM)
			|| (pawn->square->y == BOARD_COLS-1 && pawn->player_id == PLAYER_TOP)) {
		Queen *queen = new Queen(pawn);
		return true;
	}

	return false;
}
