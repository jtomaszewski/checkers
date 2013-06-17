/*
 * Game.cpp
 *
 *  Created on: 09-06-2013
 *      Author: slimak
 */

#include "Game.h"

Game::Game() {
	board = new Board();
	board->assignSquaresAndPieces();
}

Game::~Game() {
	delete board;
}

void Game::assignPlayers(PLAYER_TYPE p1, PLAYER_TYPE p2) {
	player1 = {PLAYER_TOP, p1};
	player2 = {PLAYER_BOTTOM, p2};

	current_player = &player1;
	changeTurn();
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
			FOREACH (i, moves2)
				if (!must_kill || (*i)->isKillingMove())
					moves.push_back(*i);
		}
	}

	return moves;
}

Move* Game::canMove(Move *move) {
	if (!move->to->possible)
		return NULL;

	Moves available_moves = move->from->piece->getPossibleMoves(board->squares);
	FOREACH (m, available_moves) {
		Move *m1 = *m;
		if (*m1 == *move && m1->isSingleStep())
			return *m;
	}

	return NULL;
}

bool Game::executeMove(Move *move, bool emulate) {
	FOREACH(i, move->killed_pieces) {
		if (emulate)
			(*i)->square->piece = NULL;
		else
			delete *&*i;
	}

	move->to->setPiece(move->from->piece);
	move->from->setPiece(NULL);

	if (move->isKillingMove()) {
		if (move->to->piece->canKill(board->squares)) { // jeśli z tego ruchu możemy wykonać jeszcze dalsze bicie, kontynuujemy ten ruch
			selectSquare(move->to);
			force_selected = true;
		} else { // w przeciwnym wypadku kończymy ruch
			force_selected = false;
		}
	}

	if (!force_selected) {
		tryQueenTransform(move->to->piece);
		selectSquare(NULL);
		if (!emulate)
			changeTurn();
	}

	return true;
}

bool Game::executeComputerMove() {
	Moves moves = getAllPossibleMoves(current_player->id);
	if (!moves.size())
		return false;

	int a_points = -666;
	Move *a_move = NULL;
	FOREACH(i, moves) {
		Move *m = *i;
		if (!m->full_move) continue;
		bool wasqueen = m->from->piece->type == QUEEN;
		Piece *from_piece = m->from->piece, *to_piece = m->to->piece;

		int points = m->killed_pieces.size() * 2; // + pkt za kazdego zabitego wrogiego pionka

		executeMove(m, true);
		if (!wasqueen && m->to->piece->type == QUEEN) { // +pkt jesli zdobyl damke tym ruchem
			points += 5;
			new Piece(m->to->piece);
		}

		Move *km;
		if (km = hasKillingMove(current_player == &player1 ? player2.id : player1.id)) // -pkt jesli wrog moze teraz zabic nam pionka
			points -= km->killed_pieces.size() * 2;

		FOREACH(kp, m->killed_pieces) {
			Pawn *pawn = *kp;
			pawn->square->piece = pawn;
		}
		m->from->setPiece(from_piece);
		m->to->setPiece(to_piece);

		points += (rand() % 100) > 80 ? 1 : 0; // troche losowosci

		if (points >= a_points) {
			a_points = points, a_move = m;
		}
	}

	executeMove(a_move, false);

	return true;
}

Move* Game::hasKillingMove(PLAYER_ID player) {
	Moves moves = getAllPossibleMoves(player);

	FOREACH (i, moves) {
		if ( (*i)->killed_pieces.size() ) {
			return *i;
		}
	}

	return NULL;
}

list<Pawn*> Game::getPlayerPieces(PLAYER_ID player_id) {
	list<Pawn*> pieces;
	REP(i, BOARD_SQUARES_SUM) {
		if (board->squares[i]->piece && board->squares[i]->piece->player_id == player_id)
			pieces.push_back(board->squares[i]->piece);
	}
	return pieces;
}

void Game::changeTurn() {
	current_player = ENEMY_OF(current_player, this);
	must_kill = hasKillingMove(current_player->id);

	if (!getPlayerPieces(current_player->id).size()) {
		printf("Brak pionkow! Przegrywasz!\n");
		player_win = ENEMY_OF(current_player, this);
		return;
	}

	if (!getAllPossibleMoves(current_player->id).size()) {
		printf("Nie masz już żadnych ruchów! Niestety, przegrywasz.\n");
		player_win = ENEMY_OF(current_player, this);
		return;
	}

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
		new Queen(pawn);
		return true;
	}

	return false;
}
