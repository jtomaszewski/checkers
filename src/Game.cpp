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

	if (square != NULL) {
		square->selected = true;
	}

	selected_square = square;
}

bool Game::canMove(Move *move) {
	if (!move->from->piece)
		return false;

	Moves available_moves = move->from->piece->getPossibleMoves(board->squares);
	FOREACH (m, available_moves) {
		if (*&*m == *move)
			return true;
	}

	return false;
}

bool Game::move(Move *move) {
	if (!canMove(move))
		return false;
	printf("Wykonujemy ruch z %s do %s.\n", move->from->c_str(), move->to->c_str());

	if (!move->to->piece) {
		move->to->setPiece(move->from->piece);
		move->from->setPiece(NULL);
	} else {
		removePiece(move->to->piece);
		move->to->setPiece(move->from->piece);
		move->from->setPiece(NULL);
	}

	selectSquare(NULL);
	changeTurn();

	return true;
}

void Game::removePiece(Piece *piece) {
	delete piece;
}

void Game::changeTurn() {
	current_player = current_player == player1 ? player2 : player1;
}
